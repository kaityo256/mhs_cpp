$MAX=8

class Integer
  def to_a
    s = ""
    v = self
    $MAX.times do |i|
      if (1<<($MAX-i-1)) & v !=0
        s = s + ($MAX-i).to_s  + " "
      end
    end
    s.chop
  end
  def to_b s = ""
    v = self
    $MAX.times{|i|
      s = (v&1).to_s + s
      v = v >> 1
    }
    s
  end
end

def make_array(l,n)
  r = []
  a = [1] * l + [0] * ($MAX-l)
  n.times do
    r.push a.shuffle.join("").to_i(2)
  end
  r
end

if ARGV.size < 3
  puts "usage:"
  puts "$ ruby gen.rb max size num"
  exit
end

$MAX = ARGV[0].to_i
size= ARGV[1].to_i
num = ARGV[2].to_i
make_array(size,num).each do |v|
  puts v.to_b
end

