I wanted to export all photos from google photos and keep them on a local storage.
I downloaded the google photos takeout and extracted the zip file.
I had to download the google photos takeout in small batches because it was too big.
I ended up with a folder structure like this:
```
Google Photos
├── 2015-01-01
│   ├── 20150101_000000.jpg
│   ├── 20150101_000001.jpg
│   ├── 20150101_000000.jpg.json
│   ├── 20150101_000001.jpg.json
```
I wanted to move all the photos to a single folder and rename them to the date and time they were taken.

This cpp script renames all the photos using the json files and moves them to a single folder.

All the photos which do not have a json file associated are still renamed based on the date present in the filename.


USING THIS SCRIPT

Just copy rooster.exe to the folder where you have the photos and run it by opening powershell in that folder and typing `.\rooster.exe`.
