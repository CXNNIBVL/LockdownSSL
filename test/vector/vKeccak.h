#pragma once

#include "setup.h"

#include "lockdownssl/Sha3.h"
#include "lockdownssl/Shake.h"
#include "lockdownssl/Keccak.h"

//SHA3 & SHAKE vectors at https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
std::string sha3_224_test0 = "";
std::string sha3_224_expected0 = "6B 4E 03 42 36 67 DB B7 3B 6E 15 45 4F 0E B1 AB D4 59 7F 9A 1B 07 8E 3F 5B 5A 6B C7";
std::string sha3_224_test1 = "c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5 c5";
std::string sha3_224_expected1 = "93 76 81 6A BA 50 3F 72 F9 6C E7 EB 65 AC 09 5D EE E3 BE 4B F9 BB C2 A1 CB 7E 11 E0";

std::string sha3_256_test0 = "";
std::string sha3_256_expected0 = "A7 FF C6 F8 BF 1E D7 66 51 C1 47 56 A0 61 D6 62 F5 80 FF 4D E4 3B 49 FA 82 D8 0A 4B 80 F8 43 4A";
std::string sha3_256_test1 = sha3_224_test1;
std::string sha3_256_expected1 = "79 F3 8A DE C5 C2 03 07 A9 8E F7 6E 83 24 AF BF D4 6C FD 81 B2 2E 39 73 C6 5F A1 BD 9D E3 17 87";

std::string sha3_384_test0 = "";
std::string sha3_384_expected0 = "0C 63 A7 5B 84 5E 4F 7D 01 10 7D 85 2E 4C 24 85 C5 1A 50 AA AA 94 FC 61 99 5E 71 BB EE 98 3A 2A C3 71 38 31 26 4A DB 47 FB 6B D1 E0 58 D5 F0 04";
std::string sha3_384_test1 = sha3_224_test1;
std::string sha3_384_expected1 = "18 81 DE 2C A7 E4 1E F9 5D C4 73 2B 8F 5F 00 2B 18 9C C1 E4 2B 74 16 8E D1 73 26 49 CE 1D BC DD 76 19 7A 31 FD 55 EE 98 9F 2D 70 50 DD 47 3E 8F";

std::string sha3_512_test0 = "";
std::string sha3_512_expected0 = "A6 9F 73 CC A2 3A 9A C5 C8 B5 67 DC 18 5A 75 6E 97 C9 82 16 4F E2 58 59 E0 D1 DC C1 47 5C 80 A6 15 B2 12 3A F1 F5 F9 4C 11 E3 E9 40 2C 3A C5 58 F5 00 19 9D 95 B6 D3 E3 01 75 85 86 28 1D CD 26";
std::string sha3_512_test1 = sha3_224_test1;
std::string sha3_512_expected1 = "E7 6D FA D2 20 84 A8 B1 46 7F CF 2F FA 58 36 1B EC 76 28 ED F5 F3 FD C0 E4 80 5D C4 8C AE EC A8 1B 7C 13 C3 0A DF 52 A3 65 95 84 73 9A 2D F4 6B E5 89 C5 1C A1 A4 A8 41 6D F6 54 5A 1C E8 BA 00";

constexpr size_t shake128_test0_outlen = 512;
std::string shake128_test0 = "";
std::string shake128_expected0 = "7F9C2BA4E88F827D616045507605853ED73B8093F6EFBC88EB1A6EACFA66EF263CB1EEA988004B93103CFB0AEEFD2A686E01FA4A58E8A3639CA8A1E3F9AE57E235B8CC873C23DC62B8D260169AFA2F75AB916A58D974918835D25E6A435085B2BADFD6DFAAC359A5EFBB7BCC4B59D538DF9A04302E10C8BC1CBF1A0B3A5120EA17CDA7CFAD765F5623474D368CCCA8AF0007CD9F5E4C849F167A580B14AABDEFAEE7EEF47CB0FCA9767BE1FDA69419DFB927E9DF07348B196691ABAEB580B32DEF58538B8D23F87732EA63B02B4FA0F4873360E2841928CD60DD4CEE8CC0D4C922A96188D032675C8AC850933C7AFF1533B94C834ADBB69C6115BAD4692D8619F90B0CDF8A7B9C264029AC185B70B83F2801F2F4B3F70C593EA3AEEB613A7F1B1DE33FD75081F592305F2E4526EDC09631B10958F464D889F31BA010250FDA7F1368EC2967FC84EF2AE9AFF268E0B1700AFFC6820B523A3D917135F2DFF2EE06BFE72B3124721D4A26C04E53A75E30E73A7A9C4A95D91C55D495E9F51DD0B5E9D83C6D5E8CE803AA62B8D654DB53D09B8DCFF273CDFEB573FAD8BCD45578BEC2E770D01EFDE86E721A3F7C6CCE275DABE6E2143F1AF18DA7EFDDC4C7B70B5E345DB93CC936BEA323491CCB38A388F546A9FF00DD4E1300B9B2153D2041D205B443E41B45A653F2A5C4492C1ADD544512DDA2529833462B71A41A45BE97290B6F";
constexpr size_t shake128_test1_outlen = 512;
std::string shake128_test1 = sha3_224_test1;
std::string shake128_expected1 = "131AB8D2B594946B9C81333F9BB6E0CE75C3B93104FA3469D3917457385DA037CF232EF7164A6D1EB448C8908186AD852D3F85A5CF28DA1AB6FE3438171978467F1C05D58C7EF38C284C41F6C2221A76F12AB1C04082660250802294FB87180213FDEF5B0ECB7DF50CA1F8555BE14D32E10F6EDCDE892C09424B29F597AFC270C904556BFCB47A7D40778D390923642B3CBD0579E60908D5A000C1D08B98EF933F806445BF87F8B009BA9E94F7266122ED7AC24E5E266C42A82FA1BBEFB7B8DB0066E16A85E0493F07DF4809AEC084A593748AC3DDE5A6D7AAE1E8B6E5352B2D71EFBB47D4CAEED5E6D633805D2D323E6FD81B4684B93A2677D45E7421C2C6AEA259B855A698FD7D13477A1FE53E5A4A6197DBEC5CE95F505B520BCD9570C4A8265A7E01F89C0C002C59BFEC6CD4A5C109258953EE5EE70CD577EE217AF21FA70178F0946C9BF6CA8751793479F6B537737E40B6ED28511D8A2D7E73EB75F8DAAC912FF906E0AB955B083BAC45A8E5E9B744C8506F37E9B4E749A184B30F43EB188D855F1B70D71FF3E50C537AC1B0F8974F0FE1A6AD295BA42F6AEC74D123A7ABEDDE6E2C0711CAB36BE5ACB1A5A11A4B1DB08BA6982EFCCD716929A7741CFC63AA4435E0B69A9063E880795C3DC5EF3272E11C497A91ACF699FEFEE206227A44C9FB359FD56AC0A9A75A743CFF6862F17D7259AB075216C0699511643B6439";

constexpr size_t shake256_test0_outlen = 512;
std::string shake256_test0 = "";
std::string shake256_expected0 = "46B9DD2B0BA88D13233B3FEB743EEB243FCD52EA62B81B82B50C27646ED5762FD75DC4DDD8C0F200CB05019D67B592F6FC821C49479AB48640292EACB3B7C4BE141E96616FB13957692CC7EDD0B45AE3DC07223C8E92937BEF84BC0EAB862853349EC75546F58FB7C2775C38462C5010D846C185C15111E595522A6BCD16CF86F3D122109E3B1FDD943B6AEC468A2D621A7C06C6A957C62B54DAFC3BE87567D677231395F6147293B68CEAB7A9E0C58D864E8EFDE4E1B9A46CBE854713672F5CAAAE314ED9083DAB4B099F8E300F01B8650F1F4B1D8FCF3F3CB53FB8E9EB2EA203BDC970F50AE55428A91F7F53AC266B28419C3778A15FD248D339EDE785FB7F5A1AAA96D313EACC890936C173CDCD0FAB882C45755FEB3AED96D477FF96390BF9A66D1368B208E21F7C10D04A3DBD4E360633E5DB4B602601C14CEA737DB3DCF722632CC77851CBDDE2AAF0A33A07B373445DF490CC8FC1E4160FF118378F11F0477DE055A81A9EDA57A4A2CFB0C83929D310912F729EC6CFA36C6AC6A75837143045D791CC85EFF5B21932F23861BCF23A52B5DA67EAF7BAAE0F5FB1369DB78F3AC45F8C4AC5671D85735CDDDB09D2B1E34A1FC066FF4A162CB263D6541274AE2FCC865F618ABE27C124CD8B074CCD516301B91875824D09958F341EF274BDAB0BAE316339894304E35877B0C28A9B1FD166C796B9CC258A064A8F57E27F2A";
constexpr size_t shake256_test1_outlen = 512;
std::string shake256_test1 = sha3_224_test1;
std::string shake256_expected1 = "CD8A920ED141AA0407A22D59288652E9D9F1A7EE0C1E7C1CA699424DA84A904D2D700CAAE7396ECE96604440577DA4F3AA22AEB8857F961C4CD8E06F0AE6610B1048A7F64E1074CD629E85AD7566048EFC4FB500B486A3309A8F26724C0ED628001A1099422468DE726F1061D99EB9E93604D5AA7467D4B1BD6484582A384317D7F47D750B8F5499512BB85A226C4243556E696F6BD072C5AA2D9B69730244B56853D16970AD817E213E470618178001C9FB56C54FEFA5FEE67D2DA524BB3B0B61EF0E9114A92CDBB6CCCB98615CFE76E3510DD88D1CC28FF99287512F24BFAFA1A76877B6F37198E3A641C68A7C42D45FA7ACC10DAE5F3CEFB7B735F12D4E589F7A456E78C0F5E4C4471FFFA5E4FA0514AE974D8C2648513B5DB494CEA847156D277AD0E141C24C7839064CD08851BC2E7CA109FD4E251C35BB0A04FB05B364FF8C4D8B59BC303E25328C09A882E952518E1A8AE0FF265D61C465896973D7490499DC639FB8502B39456791B1B6EC5BCC5D9AC36A6DF622A070D43FED781F5F149F7B62675E7D1A4D6DEC48C1C7164586EAE06A51208C0B791244D307726505C3AD4B26B6822377257AA152037560A739714A3CA79BD605547C9B78DD1F596F2D4F1791BC689A0E9B799A37339C04275733740143EF5D2B58B96A363D4E08076A1A9D7846436E4DCA5728B6F760EEF0CA92BF0BE5615E96959D767197A0BEEB";


//KECCAL vectors at https://emn178.github.io/online-tools/keccak_256.html
std::string keccak224_test0 = "";
std::string keccak224_expected0 = "f71837502ba8e10837bdd8d365adb85591895602fc552b48b7390abd";
std::string keccak224_test1 = sha3_224_test1;
std::string keccak224_expected1 = "8f8e45fdb199e0cf3bef0e1647e6e40986e620dc16c82cd4f17b37e5";

std::string keccak256_test0 = "";
std::string keccak256_expected0 = "c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470";
std::string keccak256_test1 = sha3_224_test1;
std::string keccak256_expected1 = "df5247d9373a6d163bc9f38ef0ffcbd5b0badda54e924f07acb0d1bb45b6e71f";

std::string keccak384_test0 = "";
std::string keccak384_expected0 = "2c23146a63a29acf99e73b88f8c24eaa7dc60aa771780ccc006afbfa8fe2479b2dd2b21362337441ac12b515911957ff";
std::string keccak384_test1 = sha3_224_test1;
std::string keccak384_expected1 = "74aeb48b7b280daaa356eef14b9a52c99588422cdcae63eeb40d1db8558ed6a71604a980cacfe94fe835c0e9c8cc6c8c";

std::string keccak512_test0 = "";
std::string keccak512_expected0 = "0eab42de4c3ceb9235fc91acffe746b29c29a8c366b7c60e4e67c466f36a4304c00fa9caf9d87976ba469bcbe06713b435f091ef2769fb160cdab33d3670680e";
std::string keccak512_test1 = sha3_224_test1;
std::string keccak512_expected1 = "d905b1f8fd86ca991302f558b4ba0918cd9a503d583fdc5da6b6c4b4322097f58ea0f08fc9f87b8dd5e42f72b82ce635876f26e423693d3ba0a555228b6d341b";

void VerifyKeccak()
{
    // Sha3_224 sha3_224;
    // VerifyHashFunction("Sha3_224 Test 0", sha3_224, sha3_224_test0, sha3_224_expected0);
    // VerifyHashFunction("Sha3_224 Test 1", sha3_224, sha3_224_test1, sha3_224_expected1);

    // Sha3_256 sha3_256;
    // VerifyHashFunction("Sha3_256 Test 0", sha3_256, sha3_256_test0, sha3_256_expected0);
    // VerifyHashFunction("Sha3_256 Test 1", sha3_256, sha3_256_test1, sha3_256_expected1);

    // Sha3_384 sha3_384;
    // VerifyHashFunction("Sha3_384 Test 0", sha3_384, sha3_384_test0, sha3_384_expected0);
    // VerifyHashFunction("Sha3_384 Test 1", sha3_384, sha3_384_test1, sha3_384_expected1);

    // Sha3_512 sha3_512;
    // VerifyHashFunction("Sha3_512 Test 0", sha3_512, sha3_512_test0, sha3_512_expected0);
    // VerifyHashFunction("Sha3_512 Test 1", sha3_512, sha3_512_test1, sha3_512_expected1);

    Shake_128 shake_128_test0(shake128_test0_outlen);
    VerifyHashFunction("Shake_128 Test 0", shake_128_test0, shake128_test0, shake128_expected0);

    Shake_128 shake_128_test1(shake128_test1_outlen);
    VerifyHashFunction("Shake_128 Test 1", shake_128_test1, shake128_test1, shake128_expected1);

    Shake_256 shake_256_test0(shake256_test0_outlen);
    VerifyHashFunction("Shake_256 Test 0", shake_256_test0, shake256_test0, shake256_expected0);

    Shake_256 shake_256_test1(shake256_test1_outlen);
    VerifyHashFunction("Shake_256 Test 1", shake_256_test1, shake256_test1, shake256_expected1);

    Keccak_224 keccak_224;
    VerifyHashFunction("Keccak_224 Test 0", keccak_224, keccak224_test0, keccak224_expected0);
    VerifyHashFunction("Keccak_224 Test 1", keccak_224, keccak224_test1, keccak224_expected1);

    Keccak_256 keccak_256;
    VerifyHashFunction("Keccak_256 Test 0", keccak_256, keccak256_test0, keccak256_expected0);
    VerifyHashFunction("Keccak_256 Test 1", keccak_256, keccak256_test1, keccak256_expected1);

    Keccak_384 keccak_384;
    VerifyHashFunction("Keccak_384 Test 0", keccak_384, keccak384_test0, keccak384_expected0);
    VerifyHashFunction("keccak_384 Test 1", keccak_384, keccak384_test1, keccak384_expected1);

    Keccak_512 keccak_512;
    VerifyHashFunction("Keccak_512 Test 0", keccak_512, keccak512_test0, keccak512_expected0);
    VerifyHashFunction("Keccak_512 Test 1", keccak_512, keccak512_test1, keccak512_expected1);
}