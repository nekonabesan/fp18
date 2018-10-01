require 'benchmark'
require 'bigdecimal'
require 'bigdecimal/util'
require '../modules/fp_module.rb'

=begin
演習 3 モンテカルロ法で数値積分を行うときの、精度 (有効桁数) と試行の数との関係について考察
せよ。円周率の例題を活用してもよいが、できれば別の関数を積分するプログラムを作って検
討することが望ましい。
=end
def a(n)
  begin
    raise ArgumentError if n.nil?
    m =  Array.new
    results = Array.new
    # ミラー–ラビン素数判定法を実行
    a = rabin_miller(n)
    a.each_with_index { |(key,val),i| m.push(key.to_i) if val == true }
    # ミラー–ラビン素数判定法の戻り値を検証
    results = primality_test(m)
    #File.open("fp08_03_results.txt", mode = "w"){|f|
    #  f.write(results)
    #}
    return results
  rescue => e
    return e
  end
end


def primality_test(a)
  begin
    raise ArgumentError if a.nil?
    results = Array.new
    a.each_with_index do |val,i|
      for j in 2..(val - 1) do
        results.push(val) if val % j == 0
      end
    end
    return results
  rescue => e
    return e
  end
end


def rabin_miller(n)
  begin
    raise ArgumentError if n.nil?
    results = {}
    a = Array.new(n) {|i| i }
    a.each_with_index do |val,i|
      if prime(val) == true then
        results[val.to_s] = true
      else
        results[val.to_s] = false
      end
    end
    return results
  rescue => e
    return e
  end
end


def prime(n)
  begin
    raise ArgumentError if n.nil?
    return true if n == 2
    return false if n == 1 || n & 1 == 0
    d = n-1
    d >>= 1 while d & 1 == 0
    20.times do                               # 20 は上の説明の k に相当
      a = rand(n-2) + 1
      t = d
      y = pow(a,t,n)                  # 実装コードは下にある
      while t != n-1 && y != 1 && y != n-1
        y = (y * y) % n
        t <<= 1
      end
      return false if y != n-1 && t & 1 == 0
    end
    return true
  rescue => e
    return e
  end
end


def pow(base,power,mod)
  result = 1
  while power > 0
    result = (result * base) % mod if power & 1 == 1
    base = (base * base) % mod
    power >>= 1;
  end
  return result
end


def pirandom(n)
  begin
    raise ArgumentError if n.nil?
    count = 0
    n.times do
      x = rand()
      y = rand()
      count = count + 1 if x**2 + y**2 < 1.0
    end
    return 4.0 * count / n
  rescue => e
    return e
  end
end


def makeprm(n)
  begin
    raise ArgumentError if n.nil?
    results = Array.new(0)
    for i in 2..n do
      flg = true
      for j in 2..(i - 1) do
        flg = false if i % j == 0
        break if j > (i /2)
      end
      results.push(i) if flg == true
    end
    return results
  rescue => e
    return e
  end
end
