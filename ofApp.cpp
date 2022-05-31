#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();
	ofRotateX(270);

	for (auto v : this->base_mesh.getVertices()) {

		auto rotation = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec2(v.y * 0.001 + ofGetFrameNum() * 0.005)), 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

		auto tmp_v = glm::normalize(v) * 150;
		tmp_v = glm::vec4(tmp_v, 0) * rotation;

		this->draw_mesh.addVertex(v);
		this->draw_mesh.addVertex(tmp_v);

		this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 1);
		this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 2);

		this->draw_mesh.addColor(ofColor(0, 0, 255));
		this->draw_mesh.addColor(ofColor(255, 0, 0));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int index = 0;
	for (auto& vertex : this->draw_mesh.getVertices()) {

		ofSetColor(this->draw_mesh.getColor(index++));
		ofDrawSphere(vertex, 2);
	}

	this->draw_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}