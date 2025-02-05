from __future__ import annotations

from argparse import ArgumentParser

import zmq


def main() -> None:
    parser = ArgumentParser()
    parser.add_argument("--url", default="tcp://127.0.0.1:16887")
    args = parser.parse_args()

    ctx = zmq.Context()
    s = ctx.socket(zmq.SUB)
    s.bind(args.url)
    s.subscribe(b'')

    try:
        while True:
            msg = s.recv()
            print('Got Message:\n{}'.format(msg.decode('utf-8')))
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
