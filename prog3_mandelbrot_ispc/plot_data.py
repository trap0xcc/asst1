#!/usr/bin/env python

import pandas as pd
import matplotlib.pyplot as plt


def plot(fname: string) -> None:
    df = pd.read_csv(fname)

    fig, ax = plt.subplots()

    ax.plot(df["taskCount"], df["speedup"], marker="o")

    ax.set_xlabel("Task Count")
    ax.set_ylabel("Speedup")
    ax.set_title("Speedup vs Task Count ("+fname+")")

    ax.grid(True)
    fig.tight_layout()
    fig.savefig(fname + ".png", dpi=300)

    plt.close(fig)


if __name__ == "__main__":
    for fname in ["data.csv"]:
        plot(fname)
