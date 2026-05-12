#!/usr/bin/env python

import pandas as pd
import matplotlib.pyplot as plt


def plot(fname: string) -> None:
    df = pd.read_csv(fname)

    fig, ax = plt.subplots()

    ax.plot(df["vectorWidth"], df["utilization"], marker="o")

    ax.set_xlabel("Vector Width")
    ax.set_ylabel("Utilization")
    ax.set_title("Utilization vs Vector Width ("+fname+")")

    ax.grid(True)
    fig.tight_layout()
    fig.savefig(fname + ".png", dpi=300)

    plt.close(fig)


if __name__ == "__main__":
    for fname in ["data.csv"]:
        plot(fname)
