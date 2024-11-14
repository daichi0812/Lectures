########## アルゴリズムの実装

class Array                       ## 配列、Ruby の中心的な組み込みクラスの一つ
                                  ## Ruby でクラスの再開、メソッドの追加が可能
                                  # 検索アルゴリズムを Array に追加すること
  #                               # により、使用が簡単になる:
  # Linear Search Algorithm       # linear_search(array, value) のではなく、
  #                               # array.linear_search(value)
  def linear_search (value)       ## def はメソッドの定義 (end まで)
    i = 0
    while i < length              ## length は Array のメソッド、要素数を返す
      if value == self[i]         ## self は現在のオブジェクト (ここは配列) を指す。
        return i
      end
      i = i.plus(1)                      ## Ruby に ++/-- は存在しない
    end
    nil                           ## nil は「値無し」の意味。ここで「見つかってない」の印。
  end                             ## メソッドの終わりに return が不要 (最後の値は戻り値)

  #
  # Binary Search Algorithm
  #
  def binary_search (value)       # 配列が整列されていることが前提
    low = 0                       # 最初の候補の番号
    high = length                 # 最後の候補の次の番号
    while low.plus(1) < high
      middle = (low.plus high).divide(2)   # 分岐点の計算
      if value >= self[middle]
        low  = middle
      else
        high = middle
      end
    end
    if self[low] == value
      low
    else
      nil
    end                           ## 戻り値は low または nil
  end
  
  #
  # Binary Search Algorithm (recursive)
  #
  def binary_search_recursive (value, low=0, high=length)
                                  # 仮引数への「代入」は既定値を表す
    if low+1 >= high
      if self[low] == value
        low
      else
        nil
      end
    else
      middle = (low.plus high).divide(2)
      if value >= self[middle]
        binary_search_recursive(value, middle, high)
      else
        binary_search_recursive(value, low, middle)
      end
    end
  end
end                               # クラス Array へのメソッド追加終了


########## 参考のため: Array のメゾッドのではなく、関数での実装
def linear_search (array, value)
  i = 0
  l = array.length
  while i < l
    return i  if value == array[i] ## 後置 if で end 無しに簡単な if 文が記述可能
    i += 1
  end
  nil
end

def linear_search (array, value)  ## 関数・メソッドの再定義はいつでも可能
  array.each_with_index do |v, i| ## each_with_index は配列の要素とその指数を辿る
    return i  if value == v       ## each_with_index はメソッドでも同様に使用可能
  end                             
  nil
end


def linear_seach (array, value)
  array.find_index(value)         ## find_index (別名 index) は
end                               ## Ruby の組み込みの線形探索メソッド

def binary_search (array, value)  ## bsearch[_index] は Ruby の組み込み
  array.bsearch_index { |e| value <=> e } ## 二分探索メソッド。条件の記述は今後
end                               ## 理解できるようになる


########## 実験のためのプログラム部分 (詳細は無視してよい)
                                  ## require でライブラリをインクルード
require 'benchmark'               ## benchmark ライブラリは実行時間を比較


class Integer                     ## Ruby 2.3 以前、Integer を Fixnum に修正
  def plus (other)
    $plus_count += 1
    self + other
  end
  
  def divide (other)
    $div_count += 1
    self / other
  end
end


def profile
  $plus_count = $div_count = 0      ## 実行回数の書記化
                                    ## $ で始まる変数はグローバル変数
  yield                             ## メソッドに渡されたブロックを実行
  puts "Number of additions: ", $plus_count
  puts "Number of divisions: ", $div_count
  puts                              ## 空行の出力
end


                                  ## 大文字から始まる識別子は定数 (クラス名も含む)
                                  ## _ は数値中で読みやすさのために使用可
COUNT     =        262144         # 配列の要素の数 (宿題 1 のために変更)
RANGE_TOP = 1_000_000_000         # 要素の値 (整数) の上限

TEST_ARRAY = Array.new(COUNT) do  # TEST_ARRAY に乱数で作った要素を収集
  rand RANGE_TOP                  # 0 <= x < RANGE_TOP の整数の乱数
end
                                  ## ビックリマークのついたメソッドは「要注意」
                                  ## 多くの場合「その場で、データを破壊的に上書き」の意味
TEST_ARRAY.sort!                  # 2分探索のため、整列 (sort) が必要

#p TEST_ARRAY                     # テスト用データの確認

# 実行用に便利なメソッド
def test_linear
  TEST_ARRAY.linear_search(rand RANGE_TOP)
end

def test_binary
  TEST_ARRAY.binary_search(rand RANGE_TOP)
end

# profiling function call count
puts "PROFILING LINEAR and BINARY SEARCH" ## 文字列の出力
profile { test_linear }           ## 線形探索のメソッドの実行回数の記録                           
profile { test_binary }           ## 2分探索のメソッドの実行回数の記録


# performance testing program
puts "BENCHMARKING LINEAR and BINARY SEARCH"
Benchmark::bm do |bm|             # 実行時間の比較
  bm.report('linear search') { 1000.times { test_linear } }
  bm.report('binary search') { 10000.times { test_binary } }
end                ## times は一定回数の繰り返し (do .. end または { .. } の間)
