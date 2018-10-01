class Ratio
  def initialize(a, b = 1)
    @a = a; @b = b
    if b == 0 then @a = 1; return end
    if a == 0 then @b = 1; return end
    if b < 0 then @a = -a; @b = -b end
    g = gcd(a.abs, b.abs); @a = @a/g; @b = @b/g
  end 

  def getDivisor
    return @b
  end

  def getDividend
    return @a
  end

  def to_s
    return "#{@a}/#{@b}"
  end

  def +(r)
    c = r.getDividend; d = r.getDivisor
    return Ratio.new(@a*d + @b*c, @b*d) # a/b+c/d = (ad+bc)/bd
  end

  def gcd(x, y)
    while true do
      if x > y then
        x = x % y
        if x == 0 then
          return y
        end
      else y = y % x
        if y == 0 then
          return x
        end
      end
    end
  end
end
