// Maths.cpp : �������̨Ӧ�ó������ڵ㡣
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
	MAX_CARD_FACE,  //ǰ��Ķ��л�ɫ
	CARD_JOKER,
	CARD_BIG_JOKER
};
enum CARD_TYPE{
	RED_HEART = 0,//����
	BLACK_HEART,//����
	SQURE,//����
	FLOWER,//÷��
	MAX_TYPE
};

/****
*����������struct�û���class�ò�ȷ�� ???
*set�������û�ɫ������
*get������û�ɫ������
*face��type���ǿ���ӵ�е�����,��get��set����
**/
class Card{
public:
	inline void set_face(const CARDS_FACE& face){if(face < CARD_3 || face > CARD_BIG_JOKER )return; this->face = face; }
	inline void set_type(const CARD_TYPE& type){if(type < RED_HEART || type > MAX_TYPE )return;this->type = type; }

	//��ʾ��
	inline const string get_face_name(){ return FACES[face];}
	inline const string get_type_name(){ return COLOR[type];}

	//������
	inline CARDS_FACE get_face(){ return face;}
	inline CARD_TYPE get_type(){ return type;}

private:
	CARDS_FACE face;//��������  FACE[face]//����
	CARD_TYPE  type; //4�ֻ�ɫ	COLOR[type]
	static const string FACES[16];
	static const string COLOR[5];
};

const string Card::FACES[16] = {
	"3","4","5","6","7","8","9","10","J","Q","K","A","2","","Joker","Big Joker"};
const string Card::COLOR[5] = {
	"����","����","����","÷��",""
};




 class PokerMgr
 {
 public:
	 PokerMgr(){prepare_cards();}//���캯��ʱ�Զ���������
	 void shuffle_the_cards();//ϴ��
	 
	 bool get_a_card(Card &card);  //��������������,���һ����
	 bool give_card(Card &card);//���ƣ�����˳����,ʧ�ܷ���false

 private:
	 
	 void prepare_cards();//׼��һ������
	 void reset(){this->prepare_cards();}
	 vector<Card> pile;//һ����

 };


 /*
 *ϴ���������Ҫ�㷨
 *α����
 *RankPoker(A,n)
 *for(int c = 0; c < 54; c++)
 *{
 *	swap(A[i],A[rand(1,n)]);
 *}
 *�����ڲ�����...
 **/
 void PokerMgr::shuffle_the_cards()
 {
	 this->reset();  //ϴ��ǰ׼����
	 time_t cStamp;
	 int magicNum = int(time(&cStamp));//���Խ�������ݱ��棬����������ֵ�����
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
	pile.clear();//�����һ��,clearû���ͷ�vector���ڴ棬ֻ�ǽ�size��Ϊ0�����±����ʱ���׳��쳣(�еı�����)
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
*���Ѿ�ϴ���ˣ�ֱ�ӷ���,��һ�ŵ���һ��
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

bool PokerMgr::get_a_card(Card &card)  //���һ����,ʹ����������㷽��
{
	if(pile.empty()){ //����
		return false;
	}
	int tID;
	time_t cStamp;
	srand(int(time(&cStamp)));

	tID = rand()%pile.size();
	cout<<"��ÿ���:";
	cout<<pile[tID].get_type_name();
	cout<<pile[tID].get_face_name();
	cout<<endl;
	for (auto iter = pile.begin();iter != pile.end(); iter++)
	{
		if(iter->get_face() == pile[tID].get_face() && iter->get_type() == pile[tID].get_type()){
			card = *iter;
			pile.erase(iter);  //��������ɾ��һ����
			break;
		}
	}
	return true;
}





/***
* ��Ϊ�ⲿ������ʾ������Ŀ���                                        
***/
void show_all(vector<Card> cards)
{
	cout<<"cards are :"<<endl;
	auto iter = cards.begin();
	int c = 1;
	while(iter != cards.end()){

		cout<<iter->get_type_name();
		cout<<iter->get_face_name();

		//ÿ����ʾ4����
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

void fapai()//���Ƹ�������
{
	PokerMgr Manager;
	vector<Card> player1;
	vector<Card> player2;
	vector<Card> player3;


	Manager.shuffle_the_cards(); //ϴ�� 


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

	cout<<"���һ�Ŀ���Ϊ:"<<endl;
	show_all(player1);
	cout<<endl;
	cout<<"��Ҷ��Ŀ���Ϊ:"<<endl;
	show_all(player2);
	cout<<endl;
	cout<<"������Ŀ���Ϊ:"<<endl;
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