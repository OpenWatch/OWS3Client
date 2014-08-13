//
//  OWS3Client.h
//  LiveStreamer
//
//  Created by Christopher Ballinger on 10/3/13.
//  Copyright (c) 2013 OpenWatch, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AmazonEndpoints.h"
#import "S3/AmazonS3Client.h"

/**
 *  OWS3Client, an easier way to upload files and data to S3.
 */
@interface OWS3Client : NSObject

/**
 *  Internal S3 client.
 */
@property (nonatomic, strong) AmazonS3Client *s3;

/**
 *  defaults to DISPATCH_QUEUE_PRIORITY_DEFAULT
 */
@property (nonatomic) dispatch_queue_t networkQueue;

/**
 *  defaults to dispatch_get_main_queue
 */
@property (nonatomic) dispatch_queue_t callbackQueue;

/**
 *  defaults to US East 1
 */
@property (nonatomic) AmazonRegion region;

/**
 *  defaults to YES
 */
@property (nonatomic) BOOL useSSL;

/**
 *  Do not bundle AWS secret keys with your application.
 *  http://mobile.awsblog.com/post/Tx31X75XISXHRH8/Managing-Credentials-in-Mobile-Applications
 *
 *  @param accessKey AWS access key
 *  @param secretKey AWS secret key
 *
 *  @return OWS3Client
 */
- (instancetype) initWithAccessKey:(NSString*)accessKey secretKey:(NSString*)secretKey;

/**
 Adds an object to a bucket using forms.
 
 @param path The path to the local file.
 @param bucket The destination bucket.
 @param key Optional. Defaults to the last path component of `path`.
 @param acl Optional. If unset it uses the global value for acl which defaults to public-read. You probably want either public-read or private. For more info check out S3CannedACL.h in aws-sdk-ios.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes a single argument: the response object from the server.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes a single argument: the `NSError` object describing error that occurred.
 */
- (void)postObjectWithFile:(NSString *)path
                    bucket:(NSString*)bucket
                       key:(NSString *)key
                       acl:(NSString*)acl
                   success:(void (^)(S3PutObjectResponse *responseObject))success
                   failure:(void (^)(NSError *error))failure;

/**
 Adds an object to a bucket using forms.
 
 @param path The path to the local file.
 @param bucket The destination bucket.
 @param key Optional. Defaults to the last path component of `path`.
 @param acl Optional. If unset it uses the global value for acl which defaults to public-read. You probably want either public-read or private. For more info check out S3CannedACL.h in aws-sdk-ios.
 @param cacheControl Optional. Can be useful for frequently-changing objects behind Cloudfront.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes a single argument: the response object from the server.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes a single argument: the `NSError` object describing error that occurred.
 */
- (void)postObjectWithFile:(NSString *)path
                    bucket:(NSString*)bucket
                       key:(NSString *)key
                       acl:(NSString*)acl
              cacheControl:(NSString*)cacheControl
                   success:(void (^)(S3PutObjectResponse *responseObject))success
                   failure:(void (^)(NSError *error))failure;

/**
 Adds an object to a bucket using forms.
 
 @param data The data you want to upload.
 @param bucket The destination bucket.
 @param key Optional. Defaults to the last path component of `path`.
 @param acl Optional. If unset it uses the global value for acl which defaults to public-read. You probably want either public-read or private. For more info check out S3CannedACL.h in aws-sdk-ios.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes a single argument: the response object from the server.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes a single argument: the `NSError` object describing error that occurred.
 */
- (void)postObjectWithData:(NSData *)data
                    bucket:(NSString*)bucket
                       key:(NSString *)key
                       acl:(NSString*)acl
                   success:(void (^)(S3PutObjectResponse *responseObject))success
                   failure:(void (^)(NSError *error))failure;

/**
 Adds an object to a bucket using forms.
 
 @param data The data you want to upload.
 @param bucket The destination bucket.
 @param key Optional. Defaults to the last path component of `path`.
 @param acl Optional. If unset it uses the global value for acl which defaults to public-read. You probably want either public-read or private. For more info check out S3CannedACL.h in aws-sdk-ios.
 @param cacheControl Optional. Can be useful for frequently-changing objects behind Cloudfront.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes a single argument: the response object from the server.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes a single argument: the `NSError` object describing error that occurred.
 */
- (void)postObjectWithData:(NSData *)data
                    bucket:(NSString*)bucket
                       key:(NSString *)key
                       acl:(NSString*)acl
              cacheControl:(NSString*)cacheControl
                   success:(void (^)(S3PutObjectResponse *responseObject))success
                   failure:(void (^)(NSError *error))failure;
                   
/* Hack: Exposed raw PUT request operation, so that custom meta data can be provided with the request (not supported by other methods) */
- (void) putS3ObjectRequest:(S3PutObjectRequest*)request
                        acl:(NSString*)acl
               cacheControl:(NSString *)cacheControl
                    success:(void (^)(S3PutObjectResponse *responseObject))success
                    failure:(void (^)(NSError *error))failure;
@end
