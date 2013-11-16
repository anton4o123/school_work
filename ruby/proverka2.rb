require 'csv'

all = []

CSV.foreach("results1.csv") do |row|
  names = row[0].split("_")[0..1]
  name = names[0] + " " + names[1]
  all << [name, row[2]=="true" ? 1 : 0, 0]
end

CSV.foreach("results3.csv") do |row|
  nams = row[0].split("_")[0..1]
  nam = nams[0] + " " + nams[1]
  check = nil
  all.each do |element|
    if nam == element[0]
      check=nam
    end
  end
  if check == nil
    all << [nam,0,0]
  end
  all.each do |element|
    if element[0]==nam
      if row[2]=="true"
        element[2]=1
      else
        element[2]=0
      end
    end
  end
end

names = {}

CSV.foreach("names.csv") do |row|
  names[row[1]] = row[0]
end

all.each do |element|
  puts element[0]
  element[0] = names[element[0]]
  if element[0] == nil
    element[0] = ""
  end
end

p all
all = all.sort {|a,b| a[0] <=> b[0] }

CSV.open("results.csv", "w") do |csv|
  all.each do |element|
  csv << element
end
end
