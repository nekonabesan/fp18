const int TRUE = 1;
const int FALSE = 0;
const int DENOMINATOR = 1000000;
//-----------------------------------------------------------------------------//
// 演習 3 数え上げ法によって平方根を求める C プログラムを作成しなさい。
// 精度をあげた時にどれくらいまで実用になるか検討しなさい。
//-----------------------------------------------------------------------------//
double calc1(double x){
  double dx = x / DENOMINATOR;
  for(int i = 0; i < DENOMINATOR; i++){
    double t = i * dx;
    double y = t * t - x;
    if(y >= 0){
      return t;
    }
  }
  return x;
}


//-----------------------------------------------------------------------------//
// 演習 4 区間 2 分法によって平方根を求める C プログラムを作成しなさい。
// 必要と思われる精度にしたとき、繰り返し回数がいくつになるか検討しなさい。
//-----------------------------------------------------------------------------//



//-----------------------------------------------------------------------------//
// 演習 5 ニュートン法によって平方根を求める C プログラムを作成しなさい。
// 必要と思われる精度にしたとき、繰り返し回数がいくつになるか検討しなさい。
// (ヒント: 繰り返しごとに現在の近似値を書き出すのでもよいですね。)
//-----------------------------------------------------------------------------//
