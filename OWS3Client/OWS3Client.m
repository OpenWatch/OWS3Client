//
//  OWS3Client.m
//  LiveStreamer
//
//  Created by Christopher Ballinger on 10/3/13.
//  Copyright (c) 2013 OpenWatch, Inc. All rights reserved.
//

#import "OWS3Client.h"

@implementation OWS3Client

- (id) initWithAccessKey:(NSString*)accessKey secretKey:(NSString*)secretKey {
    if (self = [super init]) {
        // Initial the S3 Client.
        // Logging Control - Do NOT use logging for non-development builds.
#ifdef DEBUG
        [AmazonLogger basicLogging];
        [AmazonLogger turnLoggingOn];
#else
        [AmazonLogger turnLoggingOff];
#endif
        [AmazonErrorHandler shouldNotThrowExceptions];
        self.s3 = [[AmazonS3Client alloc] initWithAccessKey:accessKey withSecretKey:secretKey];
        _region = US_EAST_1;
        _useSSL = YES;
        [self refreshEndpoint];
        self.networkQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        self.callbackQueue = dispatch_get_main_queue();
    }
    return self;
}

- (void) refreshEndpoint {
    self.s3.endpoint = [AmazonEndpoints s3Endpoint:self.region secure:self.useSSL];
}

- (void) setRegion:(AmazonRegion)region {
    _region = region;
    [self refreshEndpoint];
}

- (void) setUseSSL:(BOOL)useSSL {
    _useSSL = useSSL;
    [self refreshEndpoint];
}

- (void) postObjectWithData:(NSData *)data
                     bucket:(NSString *)bucket
                        key:(NSString *)key
                        acl:(NSString *)acl
               cacheControl:(NSString *)cacheControl
                    success:(void (^)(S3PutObjectResponse *))success
                    failure:(void (^)(NSError *))failure {
    S3PutObjectRequest *por = [[S3PutObjectRequest alloc] initWithKey:key inBucket:bucket];
    por.data  = data;
    [self putS3ObjectRequest:por acl:acl cacheControl:cacheControl success:success failure:failure];
}

- (void) postObjectWithData:(NSData *)data
                     bucket:(NSString *)bucket
                        key:(NSString *)key
                        acl:(NSString *)acl
                    success:(void (^)(S3PutObjectResponse *))success
                    failure:(void (^)(NSError *))failure {
    [self postObjectWithData:data bucket:bucket key:key acl:acl cacheControl:nil success:success failure:failure];
}

- (void)postObjectWithFile:(NSString *)path
                    bucket:(NSString*)bucket
                       key:(NSString *)key
                       acl:(NSString*)acl
              cacheControl:(NSString *)cacheControl
                   success:(void (^)(S3PutObjectResponse *responseObject))success
                   failure:(void (^)(NSError *error))failure {
    S3PutObjectRequest *por = [[S3PutObjectRequest alloc] initWithKey:key inBucket:bucket];
    por.filename  = path;
    [self putS3ObjectRequest:por acl:acl cacheControl:cacheControl success:success failure:failure];
}

- (void) postObjectWithFile:(NSString *)path
                     bucket:(NSString *)bucket
                        key:(NSString *)key
                        acl:(NSString *)acl
                    success:(void (^)(S3PutObjectResponse *))success
                    failure:(void (^)(NSError *))failure {
    [self postObjectWithFile:path bucket:bucket key:key acl:acl cacheControl:nil success:success failure:failure];
}

- (void) putS3ObjectRequest:(S3PutObjectRequest*)request
                        acl:(NSString*)acl
               cacheControl:(NSString *)cacheControl
                    success:(void (^)(S3PutObjectResponse *responseObject))success
                    failure:(void (^)(NSError *error))failure {
    dispatch_async(_networkQueue, ^{
        S3CannedACL *cannedACL = nil;
        if (acl) {
            cannedACL = [[S3CannedACL alloc] initWithStringValue:acl];
        } else {
            cannedACL = [S3CannedACL publicRead];
        }
        request.cannedACL = cannedACL;
        request.cacheControl = cacheControl;
        
        // Put the image data into the specified s3 bucket and object.
        S3PutObjectResponse *putObjectResponse = [self.s3 putObject:request];
        
        if (putObjectResponse.error) {
            if (failure) {
                dispatch_async(_callbackQueue, ^{
                    failure(putObjectResponse.error);
                });
            }
            return;
        }
        
        if (success && putObjectResponse) {
            dispatch_async(_callbackQueue, ^{
                success(putObjectResponse);
            });
        }
    });
}

@end
