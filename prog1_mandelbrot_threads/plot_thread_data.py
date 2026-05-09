#!/usr/bin/env python

import pandas as pd
import matplotlib.pyplot as plt


def plot(fname: string) -> None:
    df = pd.read_csv(fname)

    fig, ax = plt.subplots()

    ax.plot(df["numThreads"], df["speedup"], marker="o")

    ax.set_xlabel("Number of Threads")
    ax.set_ylabel("Speedup")
    ax.set_title("Speedup vs Threads ("+fname+")")

    ax.grid(True)
    fig.tight_layout()
    fig.savefig(fname + ".png", dpi=300)

    plt.close(fig)


if __name__ == "__main__":
    for fname in [
        "thread_data_view_1.csv",
        "thread_data_view_2.csv",
        "thread_data_view_1_policy_2.csv",
        "thread_data_view_2_policy_2.csv",
    ]:
        plot(fname)
