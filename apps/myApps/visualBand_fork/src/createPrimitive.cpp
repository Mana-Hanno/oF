//
//  createPrimitive.cpp
//  visualBand
//
//  Created by 川口大志 on 2014/08/03.
//
//

#include "createPrimitive.h"

void createPrimitive::setup(property &p) {
    particleFlg = false;
    prop = p;
    
    ofDisableArbTex();
	ofLoadImage(texture, "dot.png");
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/shader");
#else
    shader.load("shaders/shader");
#endif
}

void createPrimitive::draw(property &p) {
    prop = p;
    if(prop.points.size() == 0) return;
    switch (prop.dType) {
        case CP_POINT:
            glDepthMask(GL_FALSE);
            ofEnableAlphaBlending();
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            ofEnablePointSprites();
            shader.begin();
            texture.bind();
            prop.vbo.draw(GL_POINTS, 0, (int)prop.points.size());
            texture.unbind();
            
            shader.end();
            ofDisablePointSprites();
            glDepthMask(GL_TRUE);
            
            break;
        case CP_LINE:
            //ofSetLineWidth(mags[0].x/10);
            ofSetLineWidth(20);
            prop.vbo.drawElements(GL_LINE_STRIP, prop.points.size());
            break;
        case CP_CYLINDER:
            for (int i = 0; i < prop.points.size(); i++) {
                ofPushMatrix();
                //glDepthMask(GL_FALSE);
                ofEnableDepthTest();
                ofSetColor(prop.colors[i].r*255, prop.colors[i].g*255, prop.colors[i].b*255,prop.colors[i].a*255);
                ofTranslate(prop.points[i].x, prop.points[i].y-prop.mags[i].x/2, prop.points[i].z);
                ofDrawCylinder(0,0,0, 10, prop.mags[i].x);
                //glDepthMask(GL_TRUE);
                ofPopMatrix();
            }
            break;
        case CP_CYLINDER_SPECTRUM:
            //if (!prop.drawBins.size()) break;
            for (int i = 0; i < prop.points.size(); i++) {
                if(prop.origMags[i] == 0)  continue ;
                ofPushMatrix();
                ofTranslate(prop.points[i].x, prop.points[i].y- prop.drawBins[(i % 10)] *200/2, prop.points[i].z);
                ofDrawCylinder(0,0,0, 10, prop.drawBins[(i % 10)] * 200);
                ofPopMatrix();
                
                //cout << (i % 10) << " " << prop.drawBins[(i % 10)] << endl;
                
            }
            break;
        case CP_RECT:
            //ofNoFill();
            for (int i = 0; i < prop.points.size(); i++) {
                ofPushMatrix();
                ofSetColor(prop.colors[i].r*255, prop.colors[i].g*255, prop.colors[i].b*255,prop.colors[i].a*255);
                ofTranslate(prop.points[i].x-prop.mags[i].x/2, prop.points[i].y-prop.mags[i].x/4, prop.points[i].z);
                ofRotate(-prop.angle, 0, 0, 1);
                //ofRect(0, 0, mags[i].x, mags[i].x/2);
                ofDrawBox(0, 0, 0, prop.mags[i].x, prop.mags[i].x, prop.mags[i].x);
                ofPopMatrix();
            }
            break;
        case CP_RECT_ROUNDED:
            for (int i = 0; i < prop.points.size(); i++) {
                ofRectRounded(prop.points[i].x-prop.mags[i].x/2, prop.points[i].y-prop.mags[i].x/4, prop.mags[i].x, prop.mags[i].x/2, prop.mags[i].x/4);
            }
            break;
        case CP_ELLIPPSE:
            for (int i = 0; i < prop.points.size(); i++) {
                ofEllipse(prop.points[i].x, prop.points[i].y, prop.mags[i].x, prop.mags[i].x/2);
                //ofRect(points[i].x-mags[i].x/2, points[i].y-mags[i].x/2, mags[i].x, mags[i].x);
            }
            break;
        case CP_LINE_IND:
            ofSetLineWidth(10);
            for (int i = 0; i < prop.points.size(); i++) {
                ofLine(prop.points[i].x, prop.points[i].y, prop.points[i].x, prop.points[i].y+prop.mags[i].x);
            }
            break;
        case CP_SPHERE:
            for (int i = 0; i < prop.points.size(); i++) {
                ofSetColor(prop.colors[i].r*255, prop.colors[i].g*255, prop.colors[i].b*255,prop.colors[i].a*255);
                ofDrawSphere(prop.points[i].x, prop.points[i].y, prop.points[i].z, prop.mags[i].x);
            }
        
            if (particleFlg) {
                for (int i = 0; i < prop.mags.size(); i++) {
                    prop.mags[i] *= 10.0;
                }
                prop.vbo.setNormalData(&prop.mags[0], prop.mags.size(), GL_DYNAMIC_DRAW);
                
                glDepthMask(GL_FALSE);
                ofEnableAlphaBlending();
                ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                ofEnablePointSprites();
                shader.begin();
                texture.bind();
                prop.vbo.draw(GL_POINTS, 0, (int)prop.points.size());
                texture.unbind();
                
                shader.end();
                ofDisablePointSprites();
                glDepthMask(GL_TRUE);

            }
            break;
        case CP_TRIANGLE:
            prop.vbo.drawElements(GL_TRIANGLE_STRIP, prop.points.size());
            break;
        case CP_TRIANGLE_IND:
            prop.angle+=5;
            //ofNoFill();
            ofSetLineWidth(10);
            for (int i = 0; i < prop.points.size(); i++) {
                ofPushMatrix();
                //glDepthMask(GL_FALSE);
                ofSetColor(prop.colors[i].r*255, prop.colors[i].g*255, prop.colors[i].b*255,prop.colors[i].a*255);
                ofTranslate(prop.points[i].x, prop.points[i].y);
                ofRotate(prop.angle, 0, 0, 1);
                /*
                ofTriangle(0,
                           -prop.mags[i].x,
                           prop.mags[i].x/-2,
                           prop.mags[i].x/2*sqrt(3),
                           prop.mags[i].x/2,
                           prop.mags[i].x/2*sqrt(3));
                 */
                ofDrawCone(0, prop.mags[i].x/-2,prop.points[i].z, prop.mags[i].x/2, prop.mags[i].x);
                //  glDepthMask(GL_TRUE);
                ofPopMatrix();
            }
            break;
        case CP_CIRCLE:
            for (int i = 0; i < prop.points.size(); i++) {
                ofSetColor(prop.colors[i].r*255, prop.colors[i].g*255, prop.colors[i].b*255);
                ofCircle(prop.points[i].x, prop.points[i].y, prop.points[i].z, prop.mags[i].x/2);
            }
        default:
            break;
    }
}
