PNG2SignedDistanceMap
=====================

PNG2SignedDistanceField is used to create a Distance Field map for use with real-time applications.
Distance Field Maps are commonly used for rendering high quality vector like font.

![Screenshot](http://raw.github.com/haydntrigg/PNG2SignedDistanceMap/master/doc/images/preview.jpg)

Source & Output
---------

* **Source Texture**:  	The process of calculation is the "brute force" method 
						thus the amount of calculations scales exponentially 
						with the source texture size. Recommended usage is
						512x512 -> 1024x1024 source texture size. Source texture
						should only contain completely black or completely white
						pixels. (See reference texture for example, res/input.png)
						Must be in PNG format!

* **Output Texture**: 	The application will output an 8bit Bitmap (.bmp) file
						that contains 0-255 information detailing the 0-1 distance
						information. Output bitmap will be same resolution as source
						bitmap.
						
Bruteforce!?!?!?
---------
The brute force method that PNG2SignedDistanceField is very slow for large textures where
the number of iterations is equal to the source width squared plus the source height squared.
If you have extremely large textures, try to split them up into smaller source images with a 
little overlap and them stitch them back together, this will let you use more cores. (Maybe this
will become an internal feature of the application...)
Be careful, too big and you will be old and grey before you see the results for yourself.