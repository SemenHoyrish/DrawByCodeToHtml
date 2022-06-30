#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

vector<string> read_file_to_vector(string filename)
{
    vector<string> lines;
    string line;
    ifstream file (filename);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

void write_file(string filename, string text)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << text;
        file.close();
    }
}

bool failed = false;

map<string, string> colors;
string get_color(string colorname)
{
	if (colors.find(colorname) != colors.end()) {
		return colors[colorname];
	}
	return "000000";
}

void report_error(string error, string sender)
{
	cout << "[Error][" << sender << "] " << error << endl;
	failed = true;
}

void rect(string &output, vector<string> args, string &log)
{
	if (args.size() < 4) {
		report_error("Wrong count of arguments to create rectangle", "RECT");
		return;
	}

	args[0] = to_string(stoi(args[0]) - stoi(args[3]) / 2);
	args[1] = to_string(stoi(args[1]) - stoi(args[2]) / 2);

	output += "<div style='position: absolute; left: " + args[0] + "px; top: " + args[1] + "px;height: " + args[2] + "px; width: " + args[3] + "px; background-color: #" + get_color(args.size() >= 5 ? args[4] : "") + "; transform: rotateZ(" + (args.size() >= 6 ? args[5] : "0") + "deg);'></div>";
	log += "Rectangle created at (" + args[0] + ";" + args[1] + ") with size [" + args[2] + ":" + args[3] + "]" + " and colored in " + (args.size() >= 5 ? args[4] : "BLACK") + "rotated for " + (args.size() >= 6 ? args[5] : "0") + "\n";
}

void circle(string &output, vector<string> args, string &log)
{
	if (args.size() < 3) {
		report_error("Wrong count of arguments to create rectangle", "CYCLE");
		return;
	}

	args[0] = to_string(stoi(args[0]) - stoi(args[2]) / 2);
	args[1] = to_string(stoi(args[1]) - stoi(args[2]) / 2);

	output += "<div style='position: absolute; left: " + args[0] + "px; top: " + args[1] + "px;height: " + args[2] + "px; width: " + args[2] + "px; border-radius: 50%; background-color: #" + get_color(args.size() >= 4 ? args[3] : "") + ";'></div>";
	log += "Circle created at (" + args[0] + ";" + args[1] + ") with radius " + args[2]  + " and colored in " + (args.size() >= 4 ? args[3] : "BLACK") + "\n";

}

void color(vector<string> args, string &log)
{
	colors.insert({args[0], args[1]});
	log += "Color created with name: " + args[0] + " and value: " + args[1] + "\n";
}

string START = "<!DOCTYPE html><html lang=\"ru\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>{NAME}</title></head><body>";
string END   = "</body></html>";

int main(int argc, char** argv) {
	if (argc != 3)
	{
		cout << "Expected arguments: inputfile, outputfile!" << endl;
		return 1;
	}

	string inputfile = argv[1];
	string outputfile = argv[2];

	vector<string> input = read_file_to_vector(inputfile);

	string output = "";
	output += START;

	string log = "";

	for (string &line : input)
	{
		string name = "";
		vector<string> arguments;
		int state = 0;
		string arg = "";
		for (char s : line)
		{
			if (s == '!') break;
			if (s == ' ') continue;

			if (s == '[') {
				state++;
				continue;
			}
			if (s == ']') {
				arguments.push_back(arg);
				arg = "";

				if (name == "rect") {
					// for(auto &aa : arguments)
					// 	cout << "----> " << aa << endl;
					rect(output, arguments, log);
				} else if (name == "circle") {
					circle(output, arguments, log);
				} else if (name == "COLOR") {
					color(arguments, log);
				} else {
					// cout << "[Error] Undefined name: " << name << endl;
					report_error("Undefined name: " + name, "MAIN");
				}

				name = "";
				arguments.erase(arguments.begin());
			}

			if (state == 0) {
				name += s;
			} else if (state == 1) {
				if (s == ',') {
					arguments.push_back(arg);
					arg = "";
				} else {
					arg += s;
				}
			}

			// cout << s << endl;
		}
	}

	output += END;

	if (!failed)
		write_file(outputfile, output);

	if (!failed)
		cout << log << endl;

	return 0;
}


