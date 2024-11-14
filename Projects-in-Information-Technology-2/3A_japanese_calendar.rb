def to_japanese_calendar(year)
    if (1868 <= year && year < 1912)
        return "Meiji #{year - 1867}"
    elsif (1912 <= year && year < 1926)
        return "Taisho #{year - 1911}"
    elsif (1926 <= year && year < 1989)
        return "Showa #{year - 1925}"
    elsif (1989 <= year && year < 2019)
        return "Heisei #{year - 1988}"
    elsif (2019 <= year && year <= 2024)
        return "Reiwa #{year - 2018}"
    elsif year < 1868
        return "too old to convert"
    elsif year > 2024
        return "too new to convert"
    end
end