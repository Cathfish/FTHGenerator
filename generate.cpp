#include <iostream>
#include <map>
#include <vector>

using namespace std;

void printPretty(vector<map<string, string> > &user) {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	string NAME = user[0]["name"];
	string SSURL = "<SPREADSHEET URL GOES HERE>";
	string FORMURL = "<BIDDING FORM URL GOES HERE>";

	cout << "Post title: " + NAME + " - FTH Contributor Page\n";
	cout << "<p>See " + NAME + "’s works <a href=\"" + user[0]["exampleURLOne"] + "\" target=\"_blank";
	cout << "\">here</a> and <a href=\"" + user[0]["exampleURLTwo"] + "\" target=\"_blank\">here!</a></p>\n";
	
	cout << "<p>\nTo contact the seller before bidding, please (" + user[0]["bidderContactInfo"] + ")</p>\n";
	cout << "<p>\nIf you have a very specific prompt and are not flexible, it’s best to contact ";
	cout << "the seller before bidding, even if it fits within their listed parameters. If you ";
	cout << "are asking for a specific kink, <b>always ask first.</b></p>\n";

	cout << "<p>\nCharities these auctions benefit: " + user[0]["orgs"] + "</p>\n";
	cout << "<p>(<a href=\"http://fandomtrumpshate.tumblr.com/faq\" target=\"_blank\">See full ";
	cout << "list at our FAQ</a>)</p>\n";

	cout << "<p><b>" + NAME + "’s offerings:</b></p><hr>\n";

	for (int i = 0; i < user.size(); i++) {
		string SUBTYPE = "n/a", RATINGS = "n/a", LENGTH = "n/a";
		string OTHER;
		if (user[i]["donationAmountInfo"].size() > 0 || user[i]["otherInfo"].size() > 0) {
			OTHER = user[i]["donationAmountInfo"] + user[i]["otherInfo"];
		}

		if (user[i]["type"] == "fic") {
			RATINGS = user[i]["ficRatings"];
			LENGTH = user[i]["ficLength"];
		} else if (user[i]["type"].find("art") != -1) {
			SUBTYPE = user[i]["artType"];
			if (user[i]["artOtherInfo"].size() > 0 || user[i]["artLimitations"].size() > 0) {
				if (OTHER == "n/a")
					OTHER = user[i]["artLimitations"] + " " + user[i]["artOtherInfo"];
				else
					OTHER += user[i]["artLimitations"] + " " + user[i]["artOtherInfo"];
			}
		} else if (user[i]["type"] == "podfic") {
			LENGTH = user[i]["podficLength"];
		} else if (user[i]["type"] == "vid") {
			LENGTH = user[i]["videoInfo"];
		} else if (user[i]["type"].find("fan labor") != -1) {
			SUBTYPE = user[i]["fanLaborType"];
			LENGTH = user[i]["fanLaborLength"];
			if (user[i]["fanLaborOtherInfo"].size() > 0 || user[i]["culturalInfo"].size() > 0) {
				if (OTHER == "n/a")
					OTHER = user[i]["fanLaborOtherInfo"] + " " + user[i]["culturalInfo"];
				else
					OTHER += user[i]["fanLaborOtherInfo"] + " " + user[i]["culturalInfo"];
			}
		}

		cout << "<p><b>" + NAME + " Auction #" << i+1 << "</b></p>\n";
		cout << "<p><b>Type of fanwork: </b>" + user[i]["type"] + "<br>\n<b>Subtype(s): </b>" + SUBTYPE + "<br>\n";
		cout << "<b>Fandom(s): </b>" + user[i]["fandoms"] + "<br>\n<b>Rating(s): </b>" + RATINGS + "<br>\n";
		cout << "<b>Length/size: </b>" + LENGTH + "<br>\n<b>Especially interested in: </b>" + user[i]["particularInterest"] + "<br>\n";
		cout << "<b>Will not: </b>" + user[i]["unwillingToAddress"] + "<br>\n<b>Notes: </b>" + OTHER + "<br></p>\n";

		cout << "<p>Auctions run from 12 January 2017 (Midnight, EST) to 19 January 2017 (Midnight, EST).";
		cout << "<b> Bids before or after this period are invalid and will not be counted.</b>";
		cout << "If you would like to bid on this auction:</p>\n";
		cout << "<p><b>Step 1:</b> Check the <a href=\"" + SSURL + "\" target=\"_blank\">bidding ";
		cout << "spreadsheet</a> to find out what the current high bid is. (Note: It may take up ";
		cout << "to five minutes for a bid to appear.)</p>\n";
		cout << "<p><b>Step 2:</b> Fill out the seller’s <a href=\"" + FORMURL + "\" target=\"_blank\">";
		cout << "bidding form</a> with a bid that is higher than the current high bid. If you want to ";
		cout << "make it harder for someone to outbid you, bid higher! <i>You will NOT be notified if ";
		cout << "someone outbids you,</i> so please bookmark this page and check frequently. You will ";
		cout << "only be notified if you are the high bidder after the auctions end.</p>\n";
	}

	cout << "<hr>\n<p>Thanks for participating in Fandom Trumps Hate!</p>\n";
}

vector<string> parseLine(string line) {
	vector<string> result;
	string value = "";
	int endQuote = -1;
	int comma = line.find(",");

	//Throw out the "Form Created" section
	line = line.substr(comma+1);
	comma = line.find(",");

	while(comma != -1) {
		endQuote = line.substr(1).find("\",");
		if (line.find("\"") == 0 && comma << endQuote) { //If the comma falls within a response
			value = line.substr(1, endQuote);
			line = line.substr(endQuote+3);
		} else {
			value = line. substr(0, comma);
			line = line.substr(comma+1);
		}
		result.push_back(value);
		comma = line.find(",");
	}
	return result;
}

void fillMap(map<string, string> &dataMap, vector<string> &data) {
	dataMap.emplace("name", data[0]);
	dataMap.emplace("exampleURLOne", data[1]);
	dataMap.emplace("exampleURLTwo", data[2]);
	dataMap.emplace("type", data[3]);
	dataMap.emplace("contactInfo", data[4]); 
	dataMap.emplace("bidderContactInfo", data[5]); //if empty use above 
	dataMap.emplace("orgs", data[6]);
	dataMap.emplace("donationAmountInfo", data[33]);
	dataMap.emplace("otherInfo", data[34]);

	if (dataMap["type"] == "fic") {
		dataMap.emplace("fandoms", data[7]);
		dataMap.emplace("particularInterest", data[8]); 
		dataMap.emplace("unwillingToAddress", data[9]);
		dataMap.emplace("ficLength", data[10]);
		dataMap.emplace("ficRatings", data[11]);
	} else if (dataMap["type"].find("art") != -1) {
		dataMap.emplace("fandoms", data[12]);
		dataMap.emplace("particularInterest", data[16]); 
		dataMap.emplace("unwillingToAddress", data[17]);
		dataMap.emplace("artType", data[13]);
		dataMap.emplace("artOtherInfo", data[14]);
		dataMap.emplace("artLimitations", data[15]);
	} else if (dataMap["type"] == "vid") {
		dataMap.emplace("fandoms", data[22]);
		dataMap.emplace("particularInterest", data[23]);
		dataMap.emplace("unwillingToAddress", data[24]);
		dataMap.emplace("videoInfo", data[25]);
	} else if (dataMap["type"] == "podfic") {
		dataMap.emplace("fandoms", data[18]);
		dataMap.emplace("particularInterest", data[19]);
		dataMap.emplace("unwillingToAddress", data[20]);
		dataMap.emplace("podficLength", data[21]);
	} else if (dataMap["type"].find("fan labor") != -1) {
		dataMap.emplace("fandoms", data[26]);
		dataMap.emplace("particularInterest", data[31]);
		dataMap.emplace("unwillingToAddress", data[32]);
		dataMap.emplace("fanLaborType", data[27]);
		dataMap.emplace("fanLaborOtherInfo", data[28]);
		dataMap.emplace("fanLaborLength", data[29]);
		dataMap.emplace("culturalInfo", data[30]);
	}
}

void feed(vector<map<string, string> > &forms) {
	string line = "";
	string partial = "";
	vector<string> parsedLine;

	while (getline(cin, line)) {
		if (line.find("so).") == -1 && line.find("erial.") == -1 && line.find(",*") == -1) {
			partial += line;
		} else {
			if (partial.size()) {
				partial += line;
				line = partial;
				partial = "";
			}
			parsedLine = parseLine(line);
			map <string, string> formData;
			fillMap(formData, parsedLine);
		   	forms.push_back(formData);
		}
	}
}

int main(int argc, char* argv[]) {
	string garbage = "";
	vector<map<string, string> > forms;
	vector<map<string, string> > singleUser;
	
	getline(cin, garbage);
	feed(forms);

	singleUser.push_back(forms[0]);
	for (int i = 1; i < forms.size(); i++) {
		if (forms[i]["name"] != forms[i-1]["name"]) {
			printPretty(singleUser);
			singleUser.clear();
		}
		singleUser.push_back(forms[i]);
	}
	printPretty(singleUser);
	return 0;
}