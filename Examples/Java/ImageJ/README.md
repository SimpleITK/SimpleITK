## SimpleITK ImageJ example
This folder contains an ImageJ-plugin using SimpleITK.

The plugin itself can be found in the subfolder `src/main/java/org/simpleitk/imagej` in the `ExamplePlugin.java` class.

## How to build
Download the [Simple-ITK-Java package of your operating system](https://github.com/SimpleITK/SimpleITK/releases),
unpack it and enter the right path to the jar files in the pom.xml file of this project. 
You can then build this project using [maven](https://maven.apache.org/):

```
mvn package
```

If you want to run the `main` function from within your IDE, please put SimpleITKJava.dll 
(or the equivalend on your operating system) in the root folder of this project or add it to your Java library path.

## How to deploy
In order to deploy the development version to ImageJ or [Fiji](https://fiji.sc), change the path where your local 
ImageJ/Fiji is installed in the pom file:
```
<imagej.app.directory>C:/programs/fiji-win64/Fiji.app/</imagej.app.directory>
```

and run 

```
mvn install
```

Last but not least, you may have to copy `SimpleITKJava.dll` from the downloaded SimpleITK package to the `lib/win64` folder of Fiji:
```
Fiji.app/lib/win64/SimpleITKJava.dll
```

To check if the installation worked, run Fiji, open an image and run `Plugins>SimpleITK>Example Plugin`. 
You can change this location in the `src/resources/plugins.config` file.
