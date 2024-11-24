# definition of Student class with getters (and setters)
Student = Struct.new(:number, :familyname, :givenname, :english, :math)

# initialization of array students
students = [        
        Student.new("12345678", "Reigai",     "Taro",     80,  62), # 例外 　　太郎
        Student.new("12349875", "Reidai",     "Hanako",   76,  65), # 例題 　　花子
        Student.new("12349458", "Gambare",    "Manabu",   56,  66), # 頑張 　　学
        Student.new("12342584", "Sample",     "Tatoe",    34,  70), # サンプル 例恵
        Student.new("12348347", "Sugaku",     "Tokeko",   55, 100), # 数学 　　解子
        Student.new("12341948", "Girigiri",   "Tariyasu", 60,  60), # ぎりぎり 足康
        Student.new("12348463", "English",    "Perfect", 100,  56), # 英語 　　完璧
        Student.new("12347628", "Asobi",      "Saboro",   20,  25), # 遊日 　　サボ郎
        Student.new("12344924", "Kurikaeshi", "Mawaroh",  77,  30), # 繰返 　　回郎
        Student.new("12341369", "Seiretu",    "Junko",    69,  80)  # 整列 　　順子
  ]