require __dir__ + '/../../../modules/fp_image.rb'

class DrowImage
  def initialize
    @obj = FpImage.new
    @c_reef = {0 => [47,79,54], 1 => [51,96,69]}
  end

  def draw(sw,x0,y0,c = 0)
    begin
      raise ArgumentError if sw.nil? || x0.nil? || y0.nil?
      if sw == 'tree1' then
        puts('tree1')
        self.drowTree01(x0,y0,c)
      elsif sw == 'tree2' then
        puts('tree2')
        self.drowTree02(x0,y0,c)
      else
        return false
      end
      return true
    rescue => e
      return e
    end
  end

  def write(fname = 'test')
    begin
      @obj.writeimage("img/test.ppm")
      @onj = nil
      return true
    rescue => e
      return e
    end
  end

  def drawBackGroundImage
    begin
      #/=============================================/
      #  背景
      #/=============================================/
      @obj.rectangle(150,100,300,200,67,135,233)
      @obj.rectangle(150,160,300,80,171,255,127)
      #/=============================================/
      #  背景の山
      #/=============================================/
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(150,30,-80,120,200,120,255,255,255)
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(200,30,0,120,300,120,86,99,143)
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(40,20,-40,120,80,120,231,232,226)
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(260,20,180,120,360,120,231,232,226)
      # ellipse(x0, y0, prm_a, prm_b, r, g, b)
      #/=============================================/
      # 湖
      #/=============================================/
      @obj.ellipse(100,160,60,20,0,0,255)
      @obj.ellipse(0,180,120,40,0,0,255)
    rescue => e
      return e
    end
  end

  def drowTree01(x0,y0,c = 0)
    begin
      raise ArgumentError if x0.nil? || y0.nil?
      # rectangle(x, y, w, h, r, g, b)
      @obj.rectangle(x0, y0 + 80, 4, 40, 93, 93, 33)
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(x0, y0, x0 - 10, y0 + 40, x0 + 10, y0 + 40, @c_reef[0][0],@c_reef[0][1],@c_reef[0][2])
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(x0, y0 + 20, x0 - 15,y0 + 60, x0 + 15,y0 + 60, @c_reef[0][0],@c_reef[0][1],@c_reef[0][2])
      # triangle(x0, y0, x1, y1, x2, y2, r, g, b)
      @obj.triangle(x0, y0 + 50 ,x0 - 20 , y0 + 80, x0 + 20, y0 + 80, @c_reef[0][0],@c_reef[0][1],@c_reef[0][2])
      return true
    rescue => e
      return e
    end
  end

  def drowTree02(x0,y0,c)
    begin
      raise ArgumentError if x0.nil? || y0.nil?
      # Tree Obj01
      # rectangle(x, y, w, h, r, g, b)
      @obj.rectangle(x0, y0 + 60, 4, 40, 93, 93, 33)
      # ellipse(x0, y0, prm_a, prm_b, r, g, b)
      @obj.ellipse(x0, y0, 20, 50, @c_reef[1][0], @c_reef[1][1], @c_reef[1][2])
    rescue => e
      return e
    end
  end
end
