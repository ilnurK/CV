## Server and client to asynchronously receive the list of response codes that the client gives

The program consist of two files - `crawl.py` and `server.py`. The client side uses aiohttp and the server side uses fastapi.

The workflow is as follows:
- Server is started and listens on port 8888.
- Client (`crawl.py`) gets one or more queryable URLs as argument.
- Client submits all URLs via HTTP POST request as a JSON list to a server endpoint `/api/v1/tasks/`.
- Server responds with HTTP 201 created and a validated task object
- Task object contains status "running" and uuid4 ID.
- server then starts asynchronously sending HTTP GET requests to submitted URLs and collecting HTTP response codes, whether it's 200, 404 or some other - client keeps periodically querying endpoint `/api/v1/tasks/{received_task_id}` until server finishes processing all URLs. Then the task status should change to "ready" and the task's "result" field should contain a list of HTTP response codes for the submitted URLs.
- Client prints tab-separated HTTP response code and corresponding URL for each entry.

Server also use Redis for the cache counter and the domain counter. And after a configurable timeout server cleans up that cached entries.

