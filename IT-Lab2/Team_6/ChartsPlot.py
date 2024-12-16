import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from math import pi
import os
import matplotlib

# CSVファイルを読み込む
file1 = "average.csv"  # 1つ目のCSVファイルパス
file2 = "it2_sound_template_15822108.csv"  # 2つ目のCSVファイルパス

data1 = pd.read_csv(file1)
data2 = pd.read_csv(file2)

# 一番左の列を「ID」、それ以外を属性として扱う
attributes = list(data1.columns[1:])  # 最初の列（ID）を除く
num_attributes = len(attributes)

# フォルダ作成
output_folder = "radar_charts"
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# ラベル位置計算
angles = [n / float(num_attributes) * 2 * pi for n in range(num_attributes)]
angles += angles[:1]  # 閉じるために最初の角度を追加

# レーダーチャート作成
for i in range(min(len(data1), len(data2))):  # 行数分ループ
    # データ準備
    row_label1 = data1.iloc[i, 0]  # 行ラベル（ID）
    row_label2 = data2.iloc[i, 0]  # 行ラベル（ID）
    values1 = data1.iloc[i, 1:].values.flatten().tolist()
    values2 = data2.iloc[i, 1:].values.flatten().tolist()
    values1 += values1[:1]
    values2 += values2[:1]

    # 描画開始
    fig, ax = plt.subplots(figsize=(7, 6), subplot_kw={"polar": True})

    # データプロット
    ax.fill(angles, values1, color="blue", alpha=0.4, label="Group Average Data")
    ax.plot(angles, values1, color="blue", linewidth=2)

    ax.fill(angles, values2, color="red", alpha=0.4, label="My Data")
    ax.plot(angles, values2, color="red", linewidth=2)

    # ラベル設定
    ax.set_yticks([])
    ax.set_xticks(angles[:-1])
    ax.set_xticklabels(attributes, fontsize=8)

    # タイトルと凡例
    ax.set_title(f"Sound {i + 1}", fontsize=12)
    ax.legend(loc="upper right", bbox_to_anchor=(0.16, 0.1))

    # 保存
    output_path = os.path.join(output_folder, f"radar_chart_row_{i + 1}.png")
    plt.savefig(output_path)
    plt.close()

print(f"レーダーチャートの画像は '{output_folder}' フォルダに保存されました。")
