/*
 *	@(#)HelloUniverse.java 1.52 01/09/28 17:30:21
 *
 * Copyright (c) 1996-2001 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Minor modifications by Stefan Gustavson, ITN-LiTH (stegu@itn.liu.se)
 *
 */

import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.event.*;
import java.awt.GraphicsConfiguration;
import com.sun.j3d.utils.applet.MainFrame;
import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.geometry.Sphere;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.image.TextureLoader;
import javax.media.j3d.*;
import javax.media.j3d.Light;
import javax.vecmath.*;

public class HelloUniverse extends Applet {

    private SimpleUniverse u = null;

//SCENE ROOT

    public BranchGroup createSceneGraph() {
      // Create the root of the branch graph
      BranchGroup objRoot = new BranchGroup();

//TRANSFORM GROUPS

//View Translation TG
	Transform3D viewTrans = new Transform3D();
	Vector3f ViewVec = new Vector3f(0.0f, 0.0f, -5.0f);
	viewTrans.setTranslation(ViewVec);

	Transform3D viewRot = new Transform3D();
	viewRot.rotX(Math.PI/7.66f);
	viewTrans.mul(viewRot);

	TransformGroup viewTG = new TransformGroup(viewTrans);
	viewTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	objRoot.addChild(viewTG);

//SUN
//Sun Spinn TG
	TransformGroup SunSpinnTG = new TransformGroup();
	SunSpinnTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	viewTG.addChild(SunSpinnTG);

//Sun shape
	//SunSpinnTG.addChild(new ColorCube(0.9));

	Appearance Sapp = new Appearance();
	Texture stex = new TextureLoader("sun.png", this).getTexture();
	Sapp.setTexture(stex);

	SunSpinnTG.addChild(new Sphere(0.9f, Sphere.GENERATE_TEXTURE_COORDS, 200, Sapp));


//EARTH
//Earth Rotation TG
      // Create the TransformGroup node and initialize it to the
      // identity. Enable the TRANSFORM_WRITE capability so that
      // our behavior code can modify it at run time. Add it to
      // the root of the subgraph.
      TransformGroup EarthRotateTG = new TransformGroup();
      EarthRotateTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
      viewTG.addChild(EarthRotateTG);


//Earth Translation TG
   	  Transform3D etrans = new Transform3D();
      Vector3f transvec = new Vector3f(2.0f, 0.0f, 0.0f);
      etrans.setTranslation(transvec);

      TransformGroup EarthTransTG = new TransformGroup(etrans);
      EarthTransTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	  EarthRotateTG.addChild(EarthTransTG);

//Earth local Rot TG
	  Transform3D EarthLocRot = new Transform3D();
      EarthLocRot.rotX(Math.PI/7.66f);

      TransformGroup EarthLocRotTG = new TransformGroup(EarthLocRot);
      EarthLocRotTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	  EarthTransTG.addChild(EarthLocRotTG);

//Earth Spinn
	  TransformGroup EarthSpinnTG = new TransformGroup();
      EarthSpinnTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
      EarthLocRotTG.addChild(EarthSpinnTG);


//Earth Shape
      // Create a simple Shape3D node; add it to the scene graph.
      //EarthLocRotTG.addChild(new ColorCube(0.4));

	// Create and load a texture object, and associate it with an appearance
	Appearance Eapp = new Appearance();
	Texture etex = new TextureLoader("earth.png", this).getTexture();
	Eapp.setTexture(etex);

	// The three lines below are really only needed if lighting is applied
	//TextureAttributes EtexAttr = new TextureAttributes();
	//EtexAttr.setTextureMode(TextureAttributes.MODULATE);
	//Eapp.setTextureAttributes(EtexAttr);

	// Create a simple Shape3D node, attach the texture to it
      // and add the object to the scene graph.
	EarthSpinnTG.addChild(new Sphere(0.4f, Sphere.GENERATE_TEXTURE_COORDS, 50, Eapp));



//MOON


//Moon Orbit
	  TransformGroup MoonOrbitTG = new TransformGroup();
      MoonOrbitTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
      EarthTransTG.addChild(MoonOrbitTG);


//Moon Translation
	  Transform3D mtrans = new Transform3D();
      Vector3f mtransvec = new Vector3f(0.7f, 0.0f, 0.0f);
      mtrans.setTranslation(mtransvec);

      TransformGroup MoonTransTG = new TransformGroup(mtrans);
      MoonTransTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	  MoonOrbitTG.addChild(MoonTransTG);


//Moon Spinn
	TransformGroup MoonSpinnTG = new TransformGroup();
    MoonSpinnTG.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
    MoonTransTG.addChild(MoonSpinnTG);


//Moon Shape
	//MoonSpinnTG.addChild(new ColorCube(0.2));

	Appearance Mapp = new Appearance();
	Texture mtex = new TextureLoader("moon.png", this).getTexture();
	Mapp.setTexture(mtex);

	MoonSpinnTG.addChild(new Sphere(0.1f, Sphere.GENERATE_TEXTURE_COORDS, 40, Mapp));

//BEHAVIORS

//Earth Orbit Behavior -> BG
	  Transform3D yAxis = new Transform3D();

      // Create a new Behavior object that will perform the
      // desired operation on the specified transform and add it into the scene graph.
      Alpha rotationAlpha = new Alpha(-1, 365000); //Loops indefinitely, 4000 milliseconds long loops
      RotationInterpolator rotator =
        new RotationInterpolator(rotationAlpha, EarthRotateTG, yAxis, 0.0f, (float) Math.PI*2.0f);//Connect TG and Alpha and customize the behavior parameters
      BoundingSphere bounds =
        new BoundingSphere(new Point3d(0.0,0.0,0.0), 100.0); //Specify scheduling region (Sphere with origin in (0,0,0) and radius 100)
      rotator.setSchedulingBounds(bounds);
      objRoot.addChild(rotator);

//Earth Spinn Behavior -> BG
      Alpha EarthSpinnAlpha = new Alpha(-1, 1000);
      RotationInterpolator EarthSpinn =
        new RotationInterpolator(EarthSpinnAlpha, EarthSpinnTG, yAxis, 0.0f, (float) Math.PI*2.0f);
      EarthSpinn.setSchedulingBounds(bounds);
      objRoot.addChild(EarthSpinn);

//Sun Spinn Behavior -> BG
      Alpha SunSpinnAlpha = new Alpha(-1, 25000);
      RotationInterpolator SunSpinn =
        new RotationInterpolator(SunSpinnAlpha, SunSpinnTG, yAxis, 0.0f, (float) Math.PI*2.0f);
      SunSpinn.setSchedulingBounds(bounds);
      objRoot.addChild(SunSpinn);

//Moon Orbit Behavior -> BG
      Alpha MoonOrbitAlpha = new Alpha(-1, 27300);
      RotationInterpolator MoonOrbit =
        new RotationInterpolator(MoonOrbitAlpha, MoonOrbitTG, yAxis, 0.0f, (float) Math.PI*2.0f);
      MoonOrbit.setSchedulingBounds(bounds);
      objRoot.addChild(MoonOrbit);

//Moon Spinn Behavior -> BG
      Alpha MoonSpinnAlpha = new Alpha(-1, 0);
      RotationInterpolator MoonSpinn =
        new RotationInterpolator(MoonSpinnAlpha, MoonSpinnTG, yAxis, 0.0f, (float) Math.PI*2.0f);
      MoonSpinn.setSchedulingBounds(bounds);
      objRoot.addChild(MoonSpinn);

//Compile BG
      // Have Java 3D perform optimizations on this scene graph.
      objRoot.compile();

      return objRoot;
    }

    public HelloUniverse() {
    }

    public void init() {
      setLayout(new BorderLayout());
      GraphicsConfiguration config =
        SimpleUniverse.getPreferredConfiguration();

      Canvas3D c = new Canvas3D(config);
      add("Center", c);

      // Create a simple scene and attach it to the virtual universe
      BranchGroup scene = createSceneGraph();
      u = new SimpleUniverse(c);

      // This will move the ViewPlatform back a bit so the
      // objects in the scene can be viewed.
      u.getViewingPlatform().setNominalViewingTransform();

      u.addBranchGraph(scene);
    }

    public void destroy() {
      u.removeAllLocales();
    }

    //
    // The following allows HelloUniverse to be run as an application
    // as well as an applet
    //
    public static void main(String[] args) {
      new MainFrame(new HelloUniverse(), 1000, 600);
    }
}