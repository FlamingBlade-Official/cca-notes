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
const int N = 2e5 + 5;//喵内～要填数字哟～
ll qpow(ll x,ll y){
    ll res = 1;
    for (;y;y >>= 1,x = x * x % Mod) if (y & 1) res = res * x % Mod;
    return res;
}
//ATTENTION IS ALL YOU NEED
//DON'T GET STUCK ON ONE APPROACH!
ll date;
int year[4] = {366,365,365,365};
int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
struct Date{int year,month,day;};
Date getans(ll n,int op){ 
// assume that the first year has 366 days (starting at year 0) to get the date represent by n
// op means weather it is before(0) or after(1) 1582.10.5
    int y = 0,m = 0,d = 0;
    if (op == 0){
        ll p4 = (n - 1) / (365 * 4 + 1);
        // remind that n must be greater then 0,or there will be a zero start of a year
        // it should be 31/12/lastyaer
        n -= p4 * (365 * 4 + 1);
        for (int i = 0;i <= 4;++i){
            if (n > year[i]) {n -= year[i]; continue;}
            if (i == 0) month[1] = 29;
            else month[1] = 28;
            for (int j = 0;j <= 11;++j){
                if (n > month[j]) n -= month[j];
                else return (Date){p4 * 4 + i,j + 1,n};
            }
        }
    }
    if (op == 1){
        ll p400 = (n - 1) / (365 * 400 + 97);
        n -= p400 * (365 * 400 + 97);
        for (int i = 0;i < 400;++i){
            if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0)) month[1] = 29;
            else month[1] = 28;
            for (int j = 0;j < 12;++j){
                if (n > month[j]) n -= month[j];
                else return (Date){p400 * 400 + i,j + 1,n};
            }
        }
    }
    return (Date){0x0d000721};
}
void solve(){
    cin >> date; date++;
    if (date <= (4712 / 4) * (365 * 4 + 1) + 366){
        //BC
        Date ans = getans(date,0);
        cout << ans.day << " " << ans.month << " " << 4713 - ans.year << " BC" << endl;
        return ;
    }
    //AD    
    month[1] = 28; // initialize
    date -= (4712 / 4) * (365 * 4 + 1) + 366;
    int date_of_gregorian = 1581 * 365 + (1581 / 4);
    for (int i = 1;i <= 9;++i) date_of_gregorian += month[i];
    date_of_gregorian += 4; // 1582.10.04

    if (date <= date_of_gregorian){
        Date ans = getans(date + 366,0); // start to count from zero year so add 366
        cout << ans.day << " " << ans.month << " " << ans.year << endl;
        return ;
    }

    date += 10; // the missing ten days
    date -= 1582 / 100 - 1582 / 400; 
    // these will not be consider as leap year by getans(),so we have to manually subtract them

    Date ans = getans(date + 366,1);
    cout << ans.day << " " << ans.month << " " << ans.year << endl;
}
signed main(){
    ios :: sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}//喵内～