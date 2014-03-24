# OWS3Client

A simple way to upload files to S3 on iOS. I wrote this because I couldn't get [AFAmazonS3Client](https://github.com/AFNetworking/AFAmazonS3Client) to work at the time.

## Installation

We now use Cocoapods (and you should too). Add this to your `Podfile` and you should be good to go.

    pod 'OWS3Client'
    
This library depends on [Amazon's SDK for iOS](https://github.com/aws/aws-sdk-ios) and will be linked automatically by the podspec.

## Example Usage

```obj-c
NSString *filePath = @"/path/to/file.txt";
NSString *bucketName = @"bucket-name";
NSString *key = @"file.txt";
   OWS3Client *s3Client = [[OWS3Client alloc] initWithAccessKey:AWS_ACCESS_KEY_ID secretKey:AWS_SECRET_KEY];
   [s3Client postObjectWithFile:filePath bucket:bucketName key:key acl:@"public-read" success:^(S3PutObjectResponse *responseObject) {
                           NSLog(@"success updating manifest after uploading %@", outputFileName);
                       } failure:^(NSError *error) {
                           NSLog(@"error uplaoding manifest after %@", outputFileName);
                       }];
```              
   
## License

	The MIT License (MIT)
	
	Copyright (c) 2013 OpenWatch, Inc.
	
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
