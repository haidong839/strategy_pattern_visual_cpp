// strategy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cliext/list"
using namespace std;
using namespace System;

ref class PaymentStrategy abstract {
public:
	virtual void pay(int amount) = 0;
	~PaymentStrategy(){;}
};

ref class CreditCardStrategy : PaymentStrategy {
private:
	String^ name;
	String^ cardNumber;
	String^ cvv;
	String^ dateOfExpiry;
public:
	CreditCardStrategy(String^ nm, String^ ccNum, String^ cvv, String^ expiryDate){
		this->name=nm;
		this->cardNumber=ccNum;
		this->cvv=cvv;
		this->dateOfExpiry=expiryDate;
	}
	virtual void pay(int amount) override {
		Console::WriteLine(amount +" paid with credit/debit card");
	}
};

ref class PaypalStrategy  : PaymentStrategy {
private:
	String^ emailId;
	String^ passWd;
	String^ cvv;
	String^ dateOfExpiry;
public:
	PaypalStrategy (String^ emailId, String^ passWd){
		this->emailId=emailId;
		this->passWd=passWd;
	}
	virtual void pay(int amount) override {
		Console::WriteLine(amount +" paid using Paypal");
	}
};

ref class Item {
private:
	String^ upcCode;
	int price;
public:
	Item(String^ upc, int cost){
		this->upcCode=upc;
		this->price=cost;
	}

	String^ getUpcCode() {
		return upcCode;
	}

	int getPrice() {
		return price;
	} 
};

ref class ShoppingCart {
	cliext::list<Item^>^ items;

public:
	ShoppingCart(){
		this->items = gcnew cliext::list<Item^>();
	}

	void addItem(Item^ item){
		this->items->push_back(item);
	}

	void removeItem(Item^ item){
		this->items->remove(item);
	}

	int calculateTotal(){
		int sum = 0;
		for each (Item^ elem in items) 
			sum += elem->getPrice();
		return sum;
	}

	void pay(PaymentStrategy^ paymentMethod){
		int amount = calculateTotal();
		paymentMethod->pay(amount);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	ShoppingCart^ cart = gcnew ShoppingCart();
         
        Item^ item1 = gcnew Item("1234",10);
        Item^ item2 = gcnew Item("5678",40);
         
        cart->addItem(item1);
        cart->addItem(item2);
         
        //pay by paypal
        cart->pay(gcnew PaypalStrategy("myemail@example.com", "mypwd"));
         
        //pay by credit card
        cart->pay(gcnew CreditCardStrategy("Pankaj Kumar", "1234567890123456", "786", "12/15"));
		Console::ReadLine();
	return 0;
}

