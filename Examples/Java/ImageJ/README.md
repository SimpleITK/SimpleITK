## SimpleITK ImageJ example
This folder containas an ImageJ-plugin using SimpleITK.

The plugin itself can be found in the subfolder `src/main/java/org/simpleit/imagej` in the `ExamplePlugin` class.
If you want to run the `main` function from within your IDE, put the SimpleITKJava.dll in the root
folder of this project or add it to your Java library path.

## How to build
Download the Simple-ITK-Java package of your operating system from [here](https://github.com/SimpleITK/SimpleITK/releases),
unpack it and enter the right path to the jar files in the pom.xml file of this project. 
You can then build this project using [maven](https://maven.apache.org/):

```
mvn package
```



## How to deploy
In order to deploy the development version to Fiji, change the path where your local Fiji is installed in the pom file:
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
