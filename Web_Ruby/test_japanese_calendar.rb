require 'test/unit'

require_relative '3A_japanese_calendar.rb'

class TestJapaneseCalendar < Test::Unit::TestCase
  def test_out_of_bounds
    assert_equal "too new to convert", to_japanese_calendar(2345)
    assert_equal "too new to convert", to_japanese_calendar(2123)
    assert_equal "too new to convert", to_japanese_calendar(2033)
    assert_equal "too new to convert", to_japanese_calendar(2025)
    assert_equal "too old to convert", to_japanese_calendar(1867)
    assert_equal "too new to convert", to_japanese_calendar(2030)
    assert_equal "too new to convert", to_japanese_calendar(2025)
    assert_equal "too new to convert", to_japanese_calendar(2026)
    assert_equal "too new to convert", to_japanese_calendar(2050)
    assert_equal "too old to convert", to_japanese_calendar(1866)
    assert_equal "too old to convert", to_japanese_calendar(1865)
    assert_equal "too old to convert", to_japanese_calendar(1850)
    assert_equal "too old to convert", to_japanese_calendar(1800)
    assert_equal "too old to convert", to_japanese_calendar( 966)
  end

  def test_first_year
    assert_equal "Meiji 1", to_japanese_calendar(1868)
    assert_equal "Taisho 1", to_japanese_calendar(1912)
    assert_equal "Showa 1", to_japanese_calendar(1926)
    assert_equal "Heisei 1", to_japanese_calendar(1989)
    assert_equal "Reiwa 1", to_japanese_calendar(2019)
  end

  def test_last_year
    assert_equal "Meiji 44", to_japanese_calendar(1911)
    assert_equal "Taisho 14", to_japanese_calendar(1925)
    assert_equal "Showa 63", to_japanese_calendar(1988)
    assert_equal "Heisei 30", to_japanese_calendar(2018)
  end

  def test_other_years
    assert_equal "Meiji 2", to_japanese_calendar(1869)
    assert_equal "Meiji 10", to_japanese_calendar(1877)
    assert_equal "Meiji 20", to_japanese_calendar(1887)
    assert_equal "Meiji 19", to_japanese_calendar(1886)
    assert_equal "Taisho 2", to_japanese_calendar(1913)
    assert_equal "Taisho 11", to_japanese_calendar(1922)
    assert_equal "Showa 2", to_japanese_calendar(1927)
    assert_equal "Showa 10", to_japanese_calendar(1935)
    assert_equal "Showa 20", to_japanese_calendar(1945)
    assert_equal "Showa 30", to_japanese_calendar(1955)
    assert_equal "Showa 40", to_japanese_calendar(1965)
    assert_equal "Showa 50", to_japanese_calendar(1975)
    assert_equal "Showa 60", to_japanese_calendar(1985)
    assert_equal "Showa 62", to_japanese_calendar(1987)
    assert_equal "Heisei 2", to_japanese_calendar(1990)
    assert_equal "Heisei 10", to_japanese_calendar(1998)
    assert_equal "Heisei 11", to_japanese_calendar(1999)
    assert_equal "Heisei 12", to_japanese_calendar(2000)
    assert_equal "Heisei 13", to_japanese_calendar(2001)
    assert_equal "Heisei 22", to_japanese_calendar(2010)
    assert_equal "Heisei 23", to_japanese_calendar(2011)
    assert_equal "Heisei 24", to_japanese_calendar(2012)
    assert_equal "Heisei 25", to_japanese_calendar(2013)
    assert_equal "Heisei 26", to_japanese_calendar(2014)
    assert_equal "Heisei 27", to_japanese_calendar(2015)
    assert_equal "Heisei 28", to_japanese_calendar(2016)
    assert_equal "Heisei 29", to_japanese_calendar(2017)
    assert_equal "Reiwa 2", to_japanese_calendar(2020)
    assert_equal "Reiwa 3", to_japanese_calendar(2021)
    assert_equal "Reiwa 4", to_japanese_calendar(2022)
    assert_equal "Reiwa 5", to_japanese_calendar(2023)
    assert_equal "Reiwa 6", to_japanese_calendar(2024)
  end
end
