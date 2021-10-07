# AATKitSPM

A swift package manager that wraps AATKit and AdNetworks (Only AdNetworks with xcframework format are considered)

* For more information about inetgration steps, please refer to [our documentation](https://bitbucket.org/addapptr/aatkit-ios/wiki/Swift%20Package%20Manager). 

## Important Note
You have to add -ObjC in your build settings by following these steps:

* Click on the project navigator
* Click on your target and build settings
* Search for "other linker flags"
* Add "-ObjC"
