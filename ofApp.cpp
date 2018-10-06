#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	this->cam.begin();

	int radius = 300;
	int small_radius = 50;

	vector<ofPoint> locations;
	locations.push_back(ofPoint(-380, -380));
	locations.push_back(ofPoint(-380, 380));
	locations.push_back(ofPoint(380, -380));
	locations.push_back(ofPoint(380, 380));

	for (ofPoint location : locations) {

		ofPushMatrix();
		ofTranslate(location);

		for (int i = 0; i < 80; i++) {

			int deg_param = ofRandom(360);
			int small_deg_param = ofRandom(360);

			int deg_span = ofRandom(10) + 1;
			int small_deg_span = ofRandom(50) + 1;

			ofBeginShape();
			for (int l = 0; l < 5; l++) {

				int deg = ((deg_param + ofGetFrameNum() + l) * deg_span) % 360;
				int small_deg = ((deg_param + ofGetFrameNum() + l) * small_deg_span) % 360;

				ofPoint point = make_point(radius, deg, small_radius, small_deg);
				ofVertex(point);
			}
			ofEndShape();
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_point(float radius, float deg, float small_radius, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return ofPoint(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}