#include <iostream>
#include <string>
#include "OrderedList.h"
using namespace std;

class Box {
public:
	double volume;
	double weight;
	Box(double v, double w) :volume(v), weight(w) {}
};
class BoxVolumeDescending {
public:
	template <class it>
	static bool compare(const it &a, const it &b) {
		return a->volume > b->volume; // 1>2 false, 2>1 true
	}
};
class BoxWeightAscending {
public:
	template <class it>
	static bool compare(const it &a, const it &b) {
			return a->weight < b->weight;
		}
};
class MatchBoxByWeight {
public:
	template <class it>
	static bool compare(const it &a, const it &b) {
		return a->weight == b->weight;
	}
};
class MatchBoxByVolume {
public:
	template <class it>
	static bool compare(const it &a, const it &b) {
		return a->volume == b->volume;
	}
};

void outerror(string msg) {
	cout << "fail:" << msg;
	char z;
	cin >> z;
	exit(-1);
}

int main(int argc, char *argv[]) {
	OrderedList<Box *, BoxVolumeDescending> ol_vd;
	if (ol_vd.getLength() != 0) outerror("BVD bad length");
	OrderedList<Box *, BoxWeightAscending> ol_wa;
	if (ol_vd.getLength() != 0) outerror("BWA bad length");
	Box barr[] = { Box(7,3),Box(2,4),Box(5,9),Box(8,2),Box(1,1) };

	for (unsigned x = 0; x < 5; x++) {
		ol_vd.insert(&barr[x]);
		if (ol_vd.getLength() != x + 1) outerror("fail:BVD bad length 1");
		ol_wa.insert(&barr[x]);
		if (ol_wa.getLength() != x + 1) outerror("fail:BWA bad length 1");
	}
	cout << "Volume Descending" << endl;
	double last = 99;
	for (unsigned x = 0; x < ol_vd.getLength(); x++) {
		cout << " Vol:" << ol_vd.retrieve(x + 1)->volume << " Weight:" << ol_vd.retrieve(x + 1)->weight << endl;
		if (ol_vd.retrieve(x + 1)->volume > last) outerror("Volume descending error!"); 
		last = ol_vd.retrieve(x + 1)->volume;
	}
	cout << "Weight Ascending" << endl;
	last = 0;
	for (unsigned x = 0; x < ol_wa.getLength(); x++) {
		cout << " Vol:" << ol_wa.retrieve(x + 1)->volume << " Weight:" << ol_wa.retrieve(x + 1)->weight << endl;
		if (ol_wa.retrieve(x + 1)->weight < last) outerror("Weight ascending error!");
		last = ol_wa.retrieve(x + 1)->weight;
	}
	cout << "PASS1" << endl;
	/*
		int pos;
		pos=ol_vd.find<MatchBoxByWeight>(&barr[0]);
		cout << "Position of Box Weight:" << barr[0].weight << " in BVD list:" << pos << endl;
		if (pos!=2) outerror("incorrect list position");
		pos=ol_vd.find<MatchBoxByVolume>(&barr[0]);
		cout << "Position of Box Volume:" << barr[0].volume << " in BVD list:" << pos << endl;
		if (pos!=2) outerror("incorrect list position");
		pos=ol_wa.find<MatchBoxByWeight>(&barr[0]);
		cout << "Position of Box Weight:" << barr[0].weight << " in BWA list:" << pos << endl;
		if (pos!=3) outerror("incorrect list position");
		pos=ol_wa.find<MatchBoxByVolume>(&barr[0]);
		cout << "Position of Box Volume:" << barr[0].volume << " in BWA list:" << pos << endl;
		if (pos!=3) outerror("incorrect list position");
		cout << "PASS2" << endl;
	*/
	char z;
	cin >> z;
	return 0;
}