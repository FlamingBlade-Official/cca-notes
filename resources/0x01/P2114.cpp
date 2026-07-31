/*
「東の空から始まる世界」
「始于东方之空的世界」

まだ見ぬ明日を見ようとしてた
我尝试着去摸索看不见的明天
君の声だけを聞いて
单单是听到你的声音
世界はこんなに広いのだと
我就恍然明白这个世界
気づかせてくれた
是这样的宽广
息を吸って見上げてみよう
轻轻吸一口气 抬头向上看的话
そこは綺麗な夢に見た場所
那里正是梦中看到的那美丽的地方
柔らかな風 吹いて
轻柔的风拂过身边……
幾億もの涙が作る世界
「无数的泪珠 方才组成了现在的世界」
ねぇ 気ついてたの
呐 你意识到这一点了吗
最初の言葉 繰り返して
当初的那两句话 反复在我们两人之间传递
いつでも笑ってたいよ
一直都这样笑着
小さいな迷いは空に消えた
小小的迷惑在空中消失了

触れ合いた指いつまででも
相互交合的手指一直到永远
伝わるようにと そうっと
悄悄的向你传达这份感情
二人確かにここにいると
两个人确实在这里留下了
印を残して
深深的印记
語り合ってた星空の日に
我们一起畅谈星空的那晚
約束をした 離れないだと
约定好了，彼此都不要离开
君は笑って泣いた
你一边笑一边哭着
見つけたいよ
想要再见到你
何度も願いを込めて
一直都这样祈愿着，这份心情超越了一切
大切にしてた心が今求めた世界
这份最重要的心情全世界都已寻求不到
愛しい気持ちだけは
我对你无限的爱意
もう届いてるの 君のもとへ
已经传递到你的心里去了吗？
優しい瞳に 見つめられたら
正因为你温柔的双眼注视着我
もどかしくなる ふたりの距離を
所以两人的距离逐渐变得躁动起来
囁きながら 近づいていくの
但却又在互相的耳语之中变得越来越近
願いはひとつ
幾億もの涙が溢れたしてく
「无数的泪珠 从眼中夺眶而出」
そんな毎日を繰り返すように
就像是要重复这样的每个日子一样
僕らはまた 新しい夢を開く
我们再一次用自己的双手完成新的梦想
ねえ 二人で行こう
呐 我们两人一起上路吧
幾億もの涙が作る世界
「无数的泪珠 方才组成了现在的世界」
ねぇ 気ついてたの
呐 你意识到这一点了吗
最初の言葉 繰り返して
当初的那两句话 反复在我们两人之间传递
いつでも笑ってたいよ
无论何时 我都想将笑容奉献给你
どんな時だて傍にいるから
无论何时 我都会在你的身边
*/
#include <bits/stdc++.h>//喵内～
#define re register//喵内～
#define rep(i,a,b) for (re int i = (a);i <= (b); ++i)
#define debug(x) cout << #x << '=',print(x),putchar(' ')
#define file(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define pi pair<int,int>
#define mp(a,b) make_pair(a,b)
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
typedef long long ll;
using namespace std;//喵内～
inline ll read(){
    ll s = 0,f = 1;char c = getchar();
    while (!isdigit(c)){if (c == '-')f = -1;c = getchar();}
    while (isdigit(c)){s = (s<<3) + (s<<1) + (c ^ 48);c = getchar();}
    return s * f;
}//喵内～
void print(__int128 x){if (x < 0) {putchar('-'),print(-x);return ;}if (x >= 10) print(x / 10);putchar(x % 10 + 48);}//喵内～
const int Mod = 1e9 + 7;//喵内～要填数字哟～
//const int Mod = 998244353;//喵内～要填数字哟～
const ll INF = 0x3f3f3f3f;
const int N = 1e5 + 5;//喵内～要填数字哟～
ll qpow(ll x,ll y){
    ll res = 1;
    for (;y;y >>= 1,x = x * x % Mod) if (y & 1) res = res * x % Mod;
    return res;
}
//ATTENTION IS ALL YOU NEED
//DON'T GET STUCK ON ONE APPROACH!
int n,m;
int a[N],b[N];
signed main(){
    cin >> n >> m;
    for (int i = 1;i <= n;++i){
        string s;
        cin >> s >> b[i];
        if (s == "AND") a[i] = 0;
        if (s == "OR") a[i] = 1;
        if (s == "XOR") a[i] = 2;
    }

    int ans = 0,damage = 0;
    for (int i = 30;i >= 0;--i){
        int findans = 0,ans1 = 1,ans0 = 0;
        for (int j = n;j >= 1;--j){
            int op = (b[j] >> i & 1);
            if (a[j] == 0){ // AND
                if (op == 0) ans1 = ans0;
            } if (a[j] == 1){ // OR
                if (op == 1) ans0 = ans1;
            } if (a[j] == 2){ // XOR
                if (op == 1) swap(ans0,ans1);
            }
        }
        if (ans0){
            damage += (1 << i);
        } else if (ans1 && ans + (1 << i) <= m){
            ans += (1 << i);
            damage += (1 << i);
        }
    }

    cout << damage << endl;
    return 0;
}//喵内～