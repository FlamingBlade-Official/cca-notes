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
const int N = 155;//喵内～要填数字哟～
ll qpow(ll x,ll y){
    ll res = 1;
    for (;y;y >>= 1,x = x * x % Mod) if (y & 1) res = res * x % Mod;
    return res;
}
//ATTENTION IS ALL YOU NEED
//DON'T GET STUCK ON ONE APPROACH!
struct type{
    ll siz; int max_alignment,num; //size,max alignment,number of members in the struct
    int id[N]; // the id of the type
    string name[N]; // the name of the type
}a[N]; int cnt; // how many type are there
string name[N]; // match the id with the type
int getid(string s){ // get the id of a certain struct
    for (int i = 1;i <= cnt;++i)
        if (s == name[i]) return i;
    return 0x0d000721; // will never be used, so input a interesting number
}// can be substitute with STL map<string,int>
ll get_alignment(ll siz,ll alighment){
    if (siz == 0) return 0;
    siz = ((siz - 1) / alighment + 1) * alighment;
    return siz;
}
signed main(){
    ios :: sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;

    // let 0 be the starter point
    a[0].max_alignment = 1;
    ++cnt; name[cnt] = "byte"; a[cnt] = (type){1,1,0};
    ++cnt; name[cnt] = "short"; a[cnt] = (type){2,2,0};
    ++cnt; name[cnt] = "int"; a[cnt] = (type){4,4,0};
    ++cnt; name[cnt] = "long"; a[cnt] = (type){8,8,0};

    while (T--){
        int op; cin >> op;
        if (op == 1){
            string s; int num = 0;
            cin >> s >> num;
            ++cnt;
            a[cnt].num = num;
            name[cnt] = s;
            for (int i = 1;i <= num;++i){
                string _type,_name;
                cin >> _type >> _name;
                a[cnt].id[i] = getid(_type);
                a[cnt].name[i] = _name;
                a[cnt].max_alignment = max(a[cnt].max_alignment,
                                           a[a[cnt].id[i]].max_alignment);
            }
            //debug(a[cnt].max_alignment),cout << endl;
            for (int i = 1;i <= num;++i){
                a[cnt].siz = get_alignment(a[cnt].siz,a[a[cnt].id[i]].max_alignment);
                a[cnt].siz += a[a[cnt].id[i]].siz;
            }
            a[cnt].siz = get_alignment(a[cnt].siz,a[cnt].max_alignment);
            cout << a[cnt].siz << " " << a[cnt].max_alignment << endl;
        } if (op == 2){
            string _type,_name;
            cin >> _type >> _name;
            int id = getid(_type);
            a[0].siz = get_alignment(a[0].siz,a[id].max_alignment);
            cout << a[0].siz << endl;
            a[0].siz += a[id].siz;
            a[0].num++;
            a[0].id[a[0].num] = id;
            a[0].name[a[0].num] = _name;
        } if (op == 3){ 
            string _name; cin >> _name;
            string tmp = ""; // meaning that the string between two '.'
            int p = 0; ll ans = 0; // starting struct type and answer
            for (int i = 0;i < _name.size() + 1;++i){
                if (i == _name.size() || _name[i] == '.'){
                    ans = get_alignment(ans,a[p].max_alignment);
                    for (int j = 1;j <= a[p].num;++j){
                        ans = get_alignment(ans,a[a[p].id[j]].max_alignment);
                        if (a[p].name[j] == tmp){
                            p = a[p].id[j]; tmp = ""; break;
                        } else ans += a[a[p].id[j]].siz;
                    }
                } else tmp += _name[i];
            }
            cout << ans << endl;
        } if (op == 4){
            ll addr; cin >> addr;
            string ans[105]; int anscnt = 0; // answer
            int p = 0,find_ans = 0; ll begin = 0;
            // starting of the struct / have we found answer / the begin of the address 
            if (addr >= a[0].siz) {cout << "ERR" << endl; continue;}
            while (1){
                begin = get_alignment(begin,a[p].max_alignment);
                for (int i = 1;i <= a[p].num;++i){
                    int id = a[p].id[i];
                    begin = get_alignment(begin,a[id].max_alignment);
                    //debug(begin),puts("");
                    if (addr >= begin + a[id].siz) {begin += a[id].siz; continue;}
                    else if (addr >= begin && addr < begin + a[id].siz){
                        ans[++anscnt] = a[p].name[i];
                        p = id;
                        if (a[p].num == 0){find_ans = 1;}
                        break;
                    } else {find_ans = 2; break;}
                }
                if (find_ans == 1){
                    for (int i = 1;i <= anscnt;++i){
                        cout << ans[i];
                        if (i != anscnt) cout << ".";
                    }
                    cout << endl;
                    break;
                } if (find_ans == 2){
                    cout << "ERR" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}//喵内～