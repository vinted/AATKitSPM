# AATKitSPM

A swift package manager that wraps AATKit and AdNetworks (Only AdNetworks with xcframework format are considered)

## Steps

* In your project, click on the Project and choose your project
* Go to Swift Packages tab
* Click on the plus icon
* Enter "https://github.com/AddApptr/AATKitSPM" in the url field
* Switch to exact version and enter the current version (current version is 2.75.0)
* Click on next and wait until fetching the AATKit along with its dependencies
* Choose between the AATKit or AATKit-M1 based on your machine
* Click on finish

## Note
You have to add -ObjC in your build settings by following these steps:

* Click on the project navigator
* Click on your target and build settings
* Search for "other linker flags"
* Add "-ObjC"
