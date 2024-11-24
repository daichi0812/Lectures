require_relative "3A_japanese_calendar.rb"

while line = gets
    year = line.to_i
    print "Year #{year} in the Western calendar "
    puts "is #{to_japanese_calendar(year)} in the Japanese calendar."
end