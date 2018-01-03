#include <iostream>
#include <map>
#include <vector>

using namespace std;

//Add comments here
static map<int, string> formPosition = {
	{1, "tumblr"},
	{2, "pseud"},
	{3, "email"},
	{4, "portfolio"},
	{5, "portfolioOther"},
	{6, "orgs"},
	{8, "fandomFirst"},
	{9, "fandomFirst"},
	{10, "fandomSecond"},
	{11, "fandomSecond"},
	{12, "fandomThird"},
	{13, "fandomThird"},
	{14, "rating"},
	{15, "fanworkType"},
	{16, "fanLaborType"},
	{17, "ficLength"},
	{18, "fanArtType"},
	{20, "limitations"},
	{21, "altMinBid"},
	{22, "creatorLikes"},
	{23, "creatorDislikes"},
	{24, "creatorNotes"}
};

void printPretty(vector<map<string, string> > &user) {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	string SSURL = "<SPREADSHEET URL GOES HERE>";
	string FORMURL = "<BIDDING FORM URL GOES HERE>";
	string NAME = user[0]["pseud"] == "" ? user[0]["tumblr"] : user[0]["pseud"];

	cout << "Post title: " + NAME + " - FTH Contributor Page\n";
	cout << "<p>See " + NAME + "’s works <a href=\"" + user[0]["portfolio"] + "\" target=\"_blank\">here";
	if (user[0].count("portfolioOther")) {
		cout << "</a> and <a href=\"" + user[0]["portfolioOther"] + "\" target=\"_blank\">here";
	} 
	cout << "!</a></p>\n";
	
	cout << "<p>\nTo contact the seller before bidding, please email " + user[0]["email"] + "</p>\n";
	cout << "<p>\nIf you have a very specific prompt and are not flexible, it’s best to contact ";
	cout << "the seller before bidding, even if it fits within their listed parameters. If you ";
	cout << "are asking for a specific kink, <b>always ask first.</b></p>\n";

	cout << "<p>\nCharities these auctions benefit: " + user[0]["orgs"] + "</p>\n";
	cout << "<p>(<a href=\"https://fandomtrumpshate.tumblr.com/nonprofits\" target=\"_blank\">See full list</a>)</p>\n";

	cout << "<p><b>" + NAME + "’s offerings:</b></p><hr>\n";

	for (int i = 0; i < user.size(); i++) {
		string RATING = user[i]["rating"];
		string LENGTH = user[i].count("ficLength") ? user[i]["ficLength"] : "N/A";
		string FANDOMS = user[i]["fandomFirst"];
		if (user[i].count("fandomSecond")) { FANDOMS += ", " + user[i]["fandomSecond"]; }
		if (user[i].count("fandomThird")) { FANDOMS += ", " + user[i]["fandomThird"]; }

		string SUBTYPE = "N/A";
		if (user[i].count("fanArtType")) { SUBTYPE =  user[i]["fanArtType"]; }
		else if (user[i].count("fanLaborType")) { SUBTYPE =  user[i]["fanLaborType"]; }
		
		cout << "<p><b>" + NAME + " Auction #" << i+1 << "</b></p>\n";
		cout << "<p><b>Type of fanwork: </b>" + user[i]["fanworkType"] + "<br>\n<b>Subtype(s): </b>" + SUBTYPE + "<br>\n";
		cout << "<b>Fandom(s): </b>" + FANDOMS + "<br>\n<b>Highest rating creator will work with: </b>" + RATING + "<br>\n";
		cout << "<b>Length: </b>" + LENGTH + "<br>\n<b>Especially interested in: </b>" + user[i]["creatorLikes"] + "<br>\n";
		cout << "<b>Unwilling to address: </b>" + user[i]["creatorDislikes"] + "<br>\n<b>Notes: </b>" + user[i]["creatorNotes"] + "<br></p>\n";
		cout << "<b>Minimum Bid: </b>$";
		if (user[i].count("altMinBid")) {
			cout << user[i]["altMinBid"];
		} else { cout << "5"; }
		cout << "<br></p>\n";

		cout << "<p>Auctions run from 8 January 2018 (Midnight, EST) to 14 January 2018 (Midnight, EST).";
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

void fillMap(int position, map<string, string> &dataMap, string data) {
	string key = formPosition[position];
	if (data != "") { dataMap[key] = data; }
}

void feed(vector<map<string, string> > &forms) {
	map<string, string> parsed;
	string line = "";
	int position = 0;

	while (getline(cin, line, '\t')) {
		switch (position) {
			case 7:
				if (line.find("Yes,") > -1) { fillMap(8, parsed, "Any"); }
				break;
			case 18:
			case 19:
			case 25:
			case 26:
			case 0:
				break;
			case 27:
				position = 0;
				forms.push_back(parsed);
				parsed.clear();
				break;
			default:
				fillMap(position, parsed, line);
				break;
		}
		position++;
	}
}

int main(int argc, char* argv[]) {
	string garbage = "";
	vector<map<string, string> > forms;
	vector<map<string, string> > singleUser;
	
	//getline(cin, garbage);
	feed(forms);
	cout << forms.size() << endl;

	singleUser.push_back(forms[0]);
	for (int i = 1; i < forms.size(); i++) {
		if (forms[i]["tumblr"] != forms[i-1]["tumblr"]) {
			printPretty(singleUser);
			singleUser.clear();
		}
		singleUser.push_back(forms[i]);
	}
	printPretty(singleUser);
	return 0;
}