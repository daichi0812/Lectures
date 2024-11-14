# ファイルの読み込み
lines = File.readlines("about_CSS.txt")

# 各行に含まれる単語を配列に保存する。
words_in_lines = lines.map do |line| # words_in_lines は配列の配列
  line.scan(/\w+/)
end

# ↑ 例えば、一行目に"Hello, World"、二行目に"This is a test"だとすると
# words_in_lines = {{"Hello", "World"}, {"This", "is", "a", "test"}}となる

# 配列の配列である words_in_lines を一つの配列にまとめる(平坦化)。
words = words_in_lines.flatten; # ex) words = {"Hello", "World", "This", "is", "a", "test"}

# 単語を小文字に統一してグループ化する
grouped_words = words.group_by {|word_in_words| word_in_words.downcase};

# 単語とその出現回数を連想配列にまとめる。
word_counts = grouped_words.map do |word_in_grouped_words, counts|
  [word_in_grouped_words, counts.size]
end

# 降順にする
sorted_word_counts = word_counts.sort_by { |word, count| -count }

# ソートされた単語とそのカウントを出力
sorted_word_counts.each do |word, count|
  puts "#{word} → #{count}"
end
