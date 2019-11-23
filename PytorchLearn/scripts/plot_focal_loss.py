# encoding=utf-8

import matplotlib.pyplot as plt
import numpy as np


def plot_func(alpha):
    x = np.linspace(0, 1, 50, endpoint=False)
    y_pos_025_0 = -alpha * (1-x)**0 * np.log2(x)
    y_pos_025_05 = -alpha * (1-x)**0.5 * np.log2(x)
    y_pos_025_1 = -alpha * (1-x)**1 * np.log2(x)
    y_pos_025_2 = -alpha * (1-x)**2 * np.log2(x)
    y_pos_025_5 = -alpha * (1-x)**5 * np.log2(x)

    # print("x is {0}, y is {1}".format(x, y_pos))
    y_neg_025_2 = (alpha-1) * x**2 * np.log2((1-x))

    # print("x's type is {0}, y's type is {1}".format(type(x), type(y_pos)))

    plt.plot(
        x,
        y_pos_025_0,
        linestyle='-',
        marker='|',
        color='r',
        label='pos_alpha0.25_gamma0')
    plt.plot(
        x,
        y_pos_025_05,
        linestyle='-',
        marker=',',
        color='goldenrod',
        label='pos_alpha0.25_gamma05')
    plt.plot(
        x,
        y_pos_025_1,
        linestyle='-',
        marker='o',
        color='coral',
        label='pos_alpha0.25_gamma1')
    plt.plot(
        x,
        y_pos_025_2,
        linestyle='-',
        marker='v',
        color='azure',
        label='pos_alpha0.25_gamma2')
    plt.plot(
        x,
        y_pos_025_5,
        linestyle='-',
        marker='o',
        color='brown',
        label='pos_alpha0.25_gamma5')
    plt.plot(x, y_neg_025_2, '--', color='b', label='neg_alpha0.25_gamma2')
    plt.legend(loc='best')
    plt.show()
    # plt.savefig("pos.jpg")

def plot_func(x, alpha, gamma):
    pos = -alpha * (1-x)**gamma * np.log2(x)
    neg = (alpha-1) * x**gamma * np.log2((1-x))

    return [pos, neg]

if __name__ == "__main__":
    # plot_func(0.25)


    x = np.linspace(0, 1, 50, endpoint=False)
    # y_pos/neg_alpha_gamma
    y_pos_025_0, y_neg_025_0 = plot_func(x, 0.25, 0)
    y_pos_025_025, y_neg_025_025 = plot_func(x, 0.25, 0.25)
    y_pos_025_1, y_neg_025_1 = plot_func(x, 0.25, 1)
    y_pos_025_2, y_neg_025_2 = plot_func(x, 0.25, 2)
    y_pos_025_5, y_neg_025_5 = plot_func(x, 0.25, 5)

    # ax1 = plt.subplot(2,1,1)
    # plt.sca(ax1)

    plt.plot(x, y_pos_025_0, linestyle='-', marker='d', color='goldenrod', label='y_pos_025_0')
    plt.plot(x, y_pos_025_025, linestyle='--', marker='o', color='blue', label='y_pos_025_025')
    plt.plot(x, y_pos_025_1, linestyle='-', marker='v', color='aquamarine', label='y_pos_025_1')
    plt.plot(x, y_pos_025_2, linestyle=':', marker='x', color='lime', label='y_pos_025_2')
    plt.plot(x, y_pos_025_5, linestyle='--', marker='h', color='brown', label='y_pos_025_5')
    plt.plot(x, y_neg_025_0, linestyle='-', marker='d', color='goldenrod', label='y_neg_025_0')
    plt.plot(x, y_neg_025_025, linestyle='-', marker='o', color='blue', label='y_neg_025_025')
    plt.plot(x, y_neg_025_1, linestyle='-', marker='v', color='aquamarine', label='y_neg_025_1')
    plt.plot(x, y_neg_025_2, linestyle='-', marker='x', color='lime', label='y_neg_025_2')
    plt.plot(x, y_neg_025_5, linestyle='-', marker='h', color='brown', label='y_neg_025_5')

    plt.show()


    # ax2 = plt.subplot(2,1,2)
    # plt.sca(ax2)

    y_pos_075_5, y_neg_075_5 = plot_func(x, 0.75, 5)
    y_pos_05_5, y_neg_05_5 = plot_func(x, 0.5, 5)
    y_pos_025_5, y_neg_025_5 = plot_func(x, 0.25, 5)
    y_pos_0125_5, y_neg_0125_5 = plot_func(x, 0.125, 5)
    y_pos_00625_5, y_neg_00625_5 = plot_func(x, 0.0625, 5)
    plt.plot(x, y_pos_075_5, linestyle='-', marker='d', color='goldenrod', label='y_pos_075_5')
    plt.plot(x, y_pos_05_5, linestyle='-', marker='o', color='blue', label='y_pos_05_5')
    plt.plot(x, y_pos_025_5, linestyle='-', marker='v', color='aquamarine', label='y_pos_025_5')
    plt.plot(x, y_pos_0125_5, linestyle='-', marker='x', color='lime', label='y_pos_0125_5')
    plt.plot(x, y_pos_00625_5, linestyle='-', marker='h', color='brown', label='y_pos_00625_5')
    plt.plot(x, y_neg_075_5, linestyle='-', marker='d', color='goldenrod', label='y_neg_075_5')
    plt.plot(x, y_neg_05_5, linestyle='-', marker='o', color='blue', label='y_neg_05_5')
    plt.plot(x, y_neg_025_5, linestyle='-', marker='v', color='aquamarine', label='y_neg_025_5')
    plt.plot(x, y_neg_0125_5, linestyle='-', marker='x', color='lime', label='y_neg_0125_5')
    plt.plot(x, y_neg_00625_5, linestyle='-', marker='h', color='brown', label='y_neg_00625_5')

    plt.show()

