#define MAX 10000
#define TRUE 1
#define FALSE 0

// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
  #include "../fp13_target.h"
}

// fixtureNameはテストケース群をまとめるグループ名と考えればよい、任意の文字列
// それ以外のclass～testing::Testまではおまじないと考える
class fixtureName : public ::testing::Test {
protected:
    // fixtureNameでグループ化されたテストケースはそれぞれのテストケース実行前に
    // この関数を呼ぶ。共通の初期化処理を入れておくとテストコードがすっきりする
    virtual void SetUp(){
    }
    // SetUpと同様にテストケース実行後に呼ばれる関数。共通後始末を記述する。
    virtual void TearDown(){
    }
};

struct pat {
  char a[MAX];
};

// 成功するテストケース。細かい説明はGoogleTestのマニュアルを見てね。
//============================================================================//
// 配列を複製する処理
// @param char Array c1 参照元の配列
// @param char Array c2
// @result void
//============================================================================//
TEST_F(fixtureName, cpary){
  char *c1 = (char *)malloc(7 * sizeof(char));
  char *c2 = (char *)malloc(2 * sizeof(char));
  strcpy(c1, "^str$");
  strcpy(c2, "aa");
  cpary(c1, c2);
  EXPECT_STREQ(c1, "^str$");
  EXPECT_STREQ(c2, "^str$");
  // 領域開放
  free(c1);
  free(c2);
}

//============================================================================//
// 反転
// @param char Array
// @result void
//============================================================================//
TEST_F(fixtureName, reversal){
  char *c1 = (char *)malloc(5 * sizeof(char));
  // test01
  strcpy(c1, "^str$");
  reversal(c1);
  EXPECT_STREQ(c1, "$rts^");
  // test02
  c1 = (char *)realloc(c1 ,sizeof(char) * 10);
  strcpy(c1, "\\^abcde$");
  reversal(c1);
  EXPECT_STREQ(c1, "$edcba^\\");
  free(c1);
}

//============================================================================//
// startからlen文字を削除する処理
// @param char Array c2[]
// @param int strat
// @param int len
// @result void
//============================================================================//
TEST_F(fixtureName, concat_prefix)
{
  char *match = (char *)malloc(10 * sizeof(char));
  //test01
  strcpy(match, "^str");
  concat_prefix(match, 0, 1);
  EXPECT_STREQ(match, "str");
  //test02
  strcpy(match, "\\^str");
  concat_prefix(match, 0, 1);
  EXPECT_STREQ(match, "^str");
  // 領域開放
  free(match);
}

//============================================================================//
// c. ^(先頭に固定) を実現してみなさい。
//============================================================================//
TEST_F(fixtureName, chk_prefix)
{
  char *match = (char *)malloc(10 * sizeof(char));
  //test01
  strcpy(match, "^str");
  EXPECT_TRUE(chk_prefix(match));
  EXPECT_STREQ(match, "str");
  // test02
  strcpy(match, "string");
  EXPECT_FALSE(chk_prefix(match));
  EXPECT_STREQ(match, "string");
  //test03
  strcpy(match, "\\^str");
  EXPECT_FALSE(chk_prefix(match));
  EXPECT_STREQ(match, "^str");
  // 領域開放
  free(match);
}

//============================================================================//
// c. $(末尾に固定) を実現してみなさい。
//============================================================================//
TEST_F(fixtureName, chk_suffix)
{
  char *match = (char *)malloc(10 * sizeof(char));
  //test01
  strcpy(match, "str$");
  EXPECT_TRUE(chk_suffix(match));
  EXPECT_STREQ(match, "str");
  // test02
  strcpy(match, "string");
  EXPECT_FALSE(chk_suffix(match));
  EXPECT_STREQ(match, "string");
  //test01
  strcpy(match, "str\\$");
  EXPECT_FALSE(chk_suffix(match));
  EXPECT_STREQ(match, "str$");
  // 領域開放
  free(match);
}

//====================================================//
// pattern、pos文字目までのマッチング
// param char *match
// param char *pattern
// param int l1
// param int pos
// return int result
//====================================================//
TEST_F(fixtureName, normal_match)
{
  char *match = (char *)malloc(10 * sizeof(char));
  char *pattern = (char *)malloc(10 * sizeof(char));
  // test01
  strcpy(match, "string");
  strcpy(pattern, "str");
  int result = normal_match(match, pattern);
  EXPECT_TRUE(result);
  strcpy(pattern, "tri");
  result = normal_match(match, pattern);
  EXPECT_TRUE(result);
  strcpy(pattern, "ing");
  result = normal_match(match, pattern);
  EXPECT_TRUE(result);
  // test02
  strcpy(pattern, "abc");
  result = normal_match(match, pattern);
  EXPECT_FALSE(result);
  strcpy(pattern, "stg");
  result = normal_match(match, pattern);
  EXPECT_FALSE(result);
  strcpy(pattern, "mng");
  result = normal_match(match, pattern);
  EXPECT_FALSE(result);
  // 領域開放
  free(match);
  free(pattern);
}

TEST_F(fixtureName, mach1)
{
  char *match = (char *)malloc(10 * sizeof(char));
  char *pattern = (char *)malloc(10 * sizeof(char));
  // test01
  strcpy(match,"string");
  strcpy(pattern,"str");
  EXPECT_EQ(pattern_match(match, pattern), 1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"tri");
  EXPECT_EQ(pattern_match(match, pattern), 1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"rin");
  EXPECT_EQ(pattern_match(match, pattern), 1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"ing");
  EXPECT_EQ(pattern_match(match, pattern), 1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"sti");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"ina");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"abc");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"asr");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"nga");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // 領域開放
  free(match);
  free(pattern);
}

//====================================================//
// 大域変数nafに格納された構造体の変数aに文字を追加する処理
// param  char *pattern
// return bool
//====================================================//
TEST_F(fixtureName, addpat)
{
  struct pat *naf = (struct pat*)malloc(sizeof(struct pat)*1);
  struct pat s;
  naf[0] = s;
  naf[1] = s;
  naf[1].a[0] = '\0';
  char array[] = "str";
  //strcpy(a, "str");
  EXPECT_EQ(addpat(naf, array[0], 3), 1);
  EXPECT_EQ(addpat(naf, array[1], 3), 1);
  EXPECT_EQ(addpat(naf, array[2], 3), 1);
  EXPECT_EQ(naf[0].a[0], 0x73);
  EXPECT_EQ(naf[0].a[1], 0x74);
  EXPECT_EQ(naf[0].a[2], 0x72);
  EXPECT_EQ(naf[0].a[3], 0x00);
  free(naf);
}

TEST_F(fixtureName, raddpat)
{

}

// あえて失敗するテストケースも書いておく。
TEST_F(fixtureName, mach2)
{
  char *match = (char *)malloc(10 * sizeof(char));
  char *pattern = (char *)malloc(10 * sizeof(char));
  // test01
  strcpy(match,"string");
  pattern = NULL;
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test02
  strcpy(match,"string");
  strcpy(pattern,"");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test03
  match = NULL;
  strcpy(pattern,"str");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // test04
  strcpy(match,"");
  strcpy(pattern,"str");
  EXPECT_EQ(pattern_match(match, pattern), -1);
  // 領域開放
  free(match);
  free(pattern);
}
