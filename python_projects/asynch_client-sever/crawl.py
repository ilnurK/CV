#!/usr/bin/env python3
"""The aiohttp client that submits the URLs and recives response codes

Submits the list of URLs via HTTP POST request as a JSON list to a
server endpoint. Server responds with a task object, client then keeps
periodically querying endpoint {received_task_id} until server finishes
processing all URLs. The task's "result" field contain a list of HTTP
response codes for the submitted URLs. Client prints tab-separated
HTTP response code and corresponding URL for each entry.

The script requires argparse and re to parsing given arguments,
aiohttp, asyncio - for asynchronous request processing,
time - to check the speed of requests
"""

import argparse
import re
from aiohttp import ClientSession
from aiohttp.client_exceptions import ClientConnectorError
import asyncio
import time
from typing import List, Dict, Any


def parsing_args() -> List[str]:
    """Parsing arguments coming to the script in the terminal

    Returns
    -------
    List[str]
        The urls needed to be parsed
    """

    parser = argparse.ArgumentParser(
        description="Write one or more queryable URLs (http://ya.ru)"
        "with a delimeters '\\n', '\\t', ',', ' '"
    )

    parser.add_argument("input")
    args = parser.parse_args()
    urls: List[str] = list(filter(None, re.split(r"[\n\t ,]", args.input)))
    return urls


class ClientCheckStatuses:
    """Client submits URLs, recives response codes and prints them

    Client submits the list of URLs a JSON list to a server endpoint,
    which responds with a task object, then periodically querying
    endpoint {received_task_id}, until server finishes processing all
    URLs. Client prints tab-separated HTTP response code and
    corresponding URL.

    Attributes
    ----------
    urls: List[str]
        The URLs needed to be parsed
    host: str
        The server host
    endpoint: str
        The server endpoint
    """

    def __init__(self, urls: List[str], host: str, endpoint: str) -> None:
        """Initialization URLs needed to be parsed and server endpoint

        Parameters
        ----------
        urls: List[str]
            The URLs needed to be parsed
        host: str
            The server host
        endpoint: str
            The server endpoint
        """

        self.urls = urls
        self.host = host
        self.endpoint = endpoint

    async def make_request(self) -> None:
        """Submits URLs, recives response codes and prints them

        The main client function
        """

        async with ClientSession() as session:
            start: float = time.perf_counter()
            address: str = self.host + self.endpoint
            task: Dict[str, Any] = await self.__submit_urls(session, address)
            print(task)
            address = address + "/" + task.get("ID", 0)
            is_all: bool = False
            while not is_all:
                await asyncio.sleep(1)
                task = await self.__waiting_success(session, address)
                is_all = (
                    True if task.get("status", "running") == "ready" else False
                )
            code_url = task.get("result", [])
            for url in code_url:
                print(url)
            connects: int = task.get("connects", 0)
            cached: int = task.get("cached", 0)
            errors: int = task.get("errors", 0)
            total: int = connects + cached + errors
            print(
                f"{(time.perf_counter() - start):.3f} seconds. Total - {total}"
                f": {connects} connects, {cached} cached, {errors} errors"
            )

    async def __submit_urls(
        self, session: ClientSession, endpoint: str
    ) -> Dict[str, Any]:
        """Sends URLs via POST request as JSON list to server endpoint

        Parameters
        ----------
        session: ClientSession
            The aiohttp connection session
        endpoint: str
            The server endpoint that creates the task

        Returns
        -------
        Dict[str, Any]
            The task object as a dictionary of attributes
        """

        async with session.post(endpoint, json={"urls": self.urls}) as resp:
            return await resp.json()

    async def __waiting_success(
        self, session: ClientSession, endpoint: str
    ) -> Dict[str, Any]:
        """Querying task endpoint

        Parameters
        ----------
        session: ClientSession
            The aiohttp connection session
        endpoint: str
            The server endpoint that returns the task

        Returns
        -------
        Dict[str, Any]
            The task object as a dictionary of attributes
        """

        async with session.get(endpoint) as response:
            return await response.json()


if __name__ == "__main__":
    urls: List[str] = parsing_args()
    host: str = "http://localhost:8888"
    endpoint: str = "/api/v1/tasks"
    try:
        client = ClientCheckStatuses(urls, host, endpoint)
        asyncio.run(client.make_request())
    except ClientConnectorError as e:
        print(f"Connection error: {e}")
    except Exception as e:
        print(f"Error: {e}")
