from collections import Counter
from typing import Tuple, List


class Player:
    def __init__(self, decision=True, trust=True, name=None) -> None:
        self._decision: bool = decision
        self._other: bool = decision
        self._trust: bool = trust
        self._str: str = "player" if name is None else name
        self._idx = 0

    def __str__(self) -> str:
        return self._str

    @property
    def decision(self) -> bool:
        return self._decision

    @property
    def other(self) -> bool:
        return self._other

    @other.setter
    def other(self, other: bool) -> None:
        self._other = other

    @property
    def idx(self) -> int:
        return self._idx

    @idx.setter
    def idx(self, idx: int) -> None:
        self._idx = idx

    def make_decision(self) -> None:
        pass

    _cheat: bool = False
    _coop: bool = True


class Cheater(Player):
    def __init__(self) -> None:
        super().__init__(decision=self._cheat, name="cheater")


class Cooperator(Player):
    def __init__(self) -> None:
        super().__init__(decision=self._coop, name="cooperator")


class Copycat(Player):

    def __init__(self):
        super().__init__(decision=self._coop, name="copycat")

    def make_decision(self) -> None:
        if self._idx:
            self._decision = self._other
        else:
            self._idx += 1
            self._decision = self._coop


class Grudger(Player):
    def __init__(self) -> None:
        super().__init__(decision=self._coop, name="grudger")

    def make_decision(self) -> None:
        if self._other == self._cheat and self._idx:
            self._trust = False
        self._decision = self._coop if self._trust else self._cheat
        if not self._idx:
            self._idx += 1
            self._decision = self._coop
            self._trust = True


class Detective(Player):
    def __init__(self) -> None:
        super().__init__(decision=self._coop, name="detective")
        self._pattern = [self._coop, self._cheat,
                         self._coop, self._coop]
        self._max_idx = len(self._pattern)

    def make_decision(self) -> None:
        if not self._idx:
            self._trust = True

        if self._idx < self._max_idx:
            self._decision = self._pattern[self._idx]
            self._idx += 1
            if self._other == self._cheat:
                self._trust = False
        elif self._trust:
            self._decision = self._cheat
        else:
            self._decision = self._other


class Suzannpi(Player):
    def __init__(self) -> None:
        super().__init__(decision=self._cheat, name="suzannpi")
        self._pull: List[bool] = []
        self._other_cheates: bool = False

    def make_decision(self) -> None:
        if not self._idx:
            self._decision = self._cheat
            self._pull.clear()

        self._pull.append(self._other) if 0 < self._idx < 7 else None
        if self._idx == 2:
            if self._pull[0] == self._coop and self._pull[1] == self._cheat:
                self._decision = self._coop
                self._other_cheates = True
            self._pull.clear()
        elif self._idx == 3 and self._pull.pop() == self._cheat:
            self._decision = self._cheat
        elif self._idx == 4 and self._pull.pop() == self._coop \
                and self._other_cheates == True:
            self._decision = self._coop
        elif self._idx == 6 and self._pull.pop() == self._cheat:
            self._decision = self._cheat

        self._idx += 1


class Game(object):
    def __init__(self, matches=10) -> None:
        self.matches: int = matches
        self.registry: Counter = Counter()

    def play(self, player1: Player, player2: Player) -> None:
        temp_matches: int = self.matches
        player1.idx = 0
        player2.idx = 0
        player1.other = True
        player1.other = True
        while self.matches:
            player1.make_decision()
            player2.make_decision()
            player2.other = player1.decision
            player1.other = player2.decision
            if player1.decision and player2.decision:
                self.registry[str(player1)] += 2
                self.registry[str(player2)] += 2
            elif player1.decision and not player2.decision:
                self.registry[str(player2)] += 3
                self.registry[str(player1)] -= 1
            elif player2.decision:
                self.registry[str(player1)] += 3
                self.registry[str(player2)] -= 1
            self.matches -= 1
        self.matches = temp_matches

    def top3(self):
        [print(*m) for m in self.registry.most_common(3)]


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="The game of truth")
    parser.add_argument("-t", "--test", action="store_true",
                        help="tests turn on")
    args = parser.parse_args()

    game = Game()
    cheater = Cheater()
    cooperator = Cooperator()
    copycat = Copycat()
    grudger = Grudger()
    detective = Detective()
    suzannpi = Suzannpi()

    def test_changes(game: Game, player1: Player, player2: Player) -> Tuple[int, int]:
        temp1: int = game.registry[str(player1)]
        temp2: int = game.registry[str(player2)]
        game.play(player1, player2)
        value1: int = game.registry[str(player1)] - temp1
        value2: int = game.registry[str(player2)] - temp2
        return value1, value2

    results = []
    tests = []
    results.append(test_changes(game, cheater, cooperator))    # 1
    tests.append((30, -10))

    results.append(test_changes(game, copycat, cheater))       # 2
    tests.append((-1, 3))

    results.append(test_changes(game, copycat, cooperator))    # 3
    tests.append((20, 20))

    results.append(test_changes(game, grudger, copycat))       # 4
    tests.append((20, 20))

    results.append(test_changes(game, grudger, cheater))       # 5
    tests.append((-1, 3))

    results.append(test_changes(game, grudger, cooperator))    # 6
    tests.append((20, 20))

    results.append(test_changes(game, detective, grudger))     # 7
    tests.append((3, 7))

    results.append(test_changes(game, detective, copycat))     # 8
    tests.append((18, 18))

    results.append(test_changes(game, detective, cheater))     # 9
    tests.append((-3, 9))

    results.append(test_changes(game, detective, cooperator))  # 10
    tests.append((27, -1))

    results.append(test_changes(game, suzannpi, cooperator))   # 11
    tests.append((30, -10))

    results.append(test_changes(game, suzannpi, cheater))      # 12
    tests.append((0, 0))

    results.append(test_changes(game, suzannpi, copycat))      # 13
    tests.append((14, 14))

    results.append(test_changes(game, suzannpi, grudger))      # 14
    tests.append((2, 2))

    results.append(test_changes(game, suzannpi, detective))    # 15
    tests.append((19, 15))

    game.top3()

    if args.test:
        for i in range(len(results)):
            assert results[i] == tests[i], f"assert {i + 1}: {results[i]} != {tests[i]}"
