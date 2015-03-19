// Maths.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>
using namespace std;

enum CARDS_FACE {
	CARD_3 = 0,
	CARD_4,
	CARD_5,
	CARD_6,
	CARD_7,
	CARD_8,
	CARD_9,
	CARD_10,
	CARD_J,
	CARD_Q,
	CARD_K,
	CARD_A,
	CARD_2,
	MAX_CARD_FACE,  //前面的都有花色
	CARD_JOKER,
	CARD_BIG_JOKER
};
enum CARD_TYPE{
	RED_HEART = 0,//红桃
	BLACK_HEART,//黑桃
	SQURE,//方块
	FLOWER,//梅花
	MAX_TYPE
};

/****
*关于这里用struct好还是class好不确定 ???
*set用来设置花色和牌面
*get用来获得花色和牌面
*face和type都是卡牌拥有的属性,用get和set设置
**/
class Card{
public:
	inline void set_face(const CARDS_FACE& face){if(face < CARD_3 || face > CARD_BIG_JOKER )return; this->face = face; }
	inline void set_type(const CARD_TYPE& type){if(type < RED_HEART || type > MAX_TYPE )return;this->type = type; }

	//显示用
	inline const string get_face_name(){ return FACES[face];}
	inline const string get_type_name(){ return COLOR[type];}

	//排序用
	inline CARDS_FACE get_face(){ return face;}
	inline CARD_TYPE get_type(){ return type;}

private:
	CARDS_FACE face;//卡牌名字  FACE[face]//牌名
	CARD_TYPE  type; //4种花色	COLOR[type]
	static const string FACES[16];
	static const string COLOR[5];
};

const string Card::FACES[16] = {
	"3","4","5","6","7","8","9","10","J","Q","K","A","2","","Joker","Big Joker"};
const string Card::COLOR[5] = {
	"红桃","黑桃","方块","梅花",""
};




 class PokerMgr
 {
 public:
	 PokerMgr(){prepare_cards();}//构造函数时自动生成新牌
	 void shuffle_the_cards();//洗牌
	 
	 bool get_a_card(Card &card);  //如果卡牌是乱序的,获得一张牌
	 bool give_card(Card &card);//发牌，按照顺序发牌,失败返回false

 private:
	 
	 void prepare_cards();//准备一副新牌
	 void reset(){this->prepare_cards();}
	 vector<Card> pile;//一堆牌

 };


 /*
 *洗牌问题的主要算法
 *伪代码
 *RankPoker(A,n)
 *for(int c = 0; c < 54; c++)
 *{
 *	swap(A[i],A[rand(1,n)]);
 *}
 *类似内部排序...
 **/
 void PokerMgr::shuffle_the_cards()
 {
	 this->reset();  //洗牌前准备牌
	 time_t cStamp;
	 int magicNum = int(time(&cStamp));//可以将这个数据保存，用来再现这局的牌序
	 srand(magicNum);
	 for (int c = 0; c < 54; c++)
	 {
		 Card cExchange;
		 int unRand = rand()%54;
		cExchange =  pile[c];
		pile[c] = pile[unRand];
		pile[unRand] = cExchange;
	 }
 }

void PokerMgr::prepare_cards()
{
	pile.clear();//先清除一遍,clear没有释放vector的内存，只是将size置为0，用下标访问时会抛出异常(有的编译器)
	for (int c = 0; c < MAX_CARD_FACE; c++)
	{
		for(int k = 0; k < MAX_TYPE; k++)
		{
			Card card;
			card.set_face((CARDS_FACE)c);
			card.set_type((CARD_TYPE)k);
			pile.push_back(card);
		}

	}
	Card joker,Bjoker;
	joker.set_face(CARD_JOKER);
	joker.set_type(MAX_TYPE);
	Bjoker.set_face(CARD_BIG_JOKER);
	Bjoker.set_type(MAX_TYPE);
	pile.push_back(joker);
	pile.push_back(Bjoker);
}

/*
*牌已经洗好了，直接发牌,发一张弹出一张
*/
bool PokerMgr::give_card(Card &card)  
{
	if(pile.empty()){
		return false;
	}
	card = pile.back();
	pile.pop_back();
	return true;
}

bool PokerMgr::get_a_card(Card &card)  //获得一张牌,使用随机数计算方法
{
	if(pile.empty()){ //空了
		return false;
	}
	int tID;
	time_t cStamp;
	srand(int(time(&cStamp)));

	tID = rand()%pile.size();
	cout<<"获得卡牌:";
	cout<<pile[tID].get_type_name();
	cout<<pile[tID].get_face_name();
	cout<<endl;
	for (auto iter = pile.begin();iter != pile.end(); iter++)
	{
		if(iter->get_face() == pile[tID].get_face() && iter->get_type() == pile[tID].get_type()){
			card = *iter;
			pile.erase(iter);  //乱序里面删除一张牌
			break;
		}
	}
	return true;
}





/***
* 作为外部函数显示手里面的卡牌                                        
***/
void show_all(vector<Card> cards)
{
	cout<<"cards are :"<<endl;
	auto iter = cards.begin();
	int c = 1;
	while(iter != cards.end()){

		cout<<iter->get_type_name();
		cout<<iter->get_face_name();

		//每行显示4张牌
		if(c % 4 != 0){
			cout<<",";
		}else{
			cout<<endl;
		}
		c++;
		iter++;
	}
}


bool cmp(Card& card1,Card& card2 )
{
	if(card1.get_face() < card2.get_face()){
		return true;
	}else{
		if(card1.get_face() == card2.get_face()){
			return card1.get_type() < card2.get_type();
		}else{
			return false;
		}
	}
}

void fapai()//发牌给三个人
{
	PokerMgr Manager;
	vector<Card> player1;
	vector<Card> player2;
	vector<Card> player3;


	Manager.shuffle_the_cards(); //洗牌 


	Card c;
	int num = 0;
	while(Manager.give_card(c)){
		
		switch (num % 3)
		{
		case 0:
			player1.push_back(c);
			break;
		case 1:
			player2.push_back(c);
			break;
		case 2:
			player3.push_back(c);
			break;
		default:
			break;
		}
		++num;			
		
	}
	sort(player1.begin(),player1.end(),cmp);
	sort(player2.begin(),player2.end(),cmp);
	sort(player3.begin(),player3.end(),cmp);

	cout<<"玩家一的卡牌为:"<<endl;
	show_all(player1);
	cout<<endl;
	cout<<"玩家二的卡牌为:"<<endl;
	show_all(player2);
	cout<<endl;
	cout<<"玩家三的卡牌为:"<<endl;
	show_all(player3);
	cout<<endl;

}






int _tmain(int argc, _TCHAR* argv[])
{
	
		fapai();
//		fapai();

	
	system("pause");
	return 0;
}