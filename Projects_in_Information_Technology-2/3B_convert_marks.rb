def convert_mark(mark, exponent)
    (mark**exponent * (100.0/100**exponent)).round
end

(0..100).each do |n| 

    printf("%3d points -> %3d points\n", n, convert_mark(n, 0.5))

end