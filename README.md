

## attempt to create a s3-hosted static website via AWS CLI

This is based on the manual steps at https://docs.aws.amazon.com/AmazonS3/latest/userguide/HostingWebsiteOnS3Setup.html

If I follow the 'manual' procedure, the static website works as expected.

If I use this script, browsers want to 'download' the files, rather than 'interpreting' them.  Why ?


```
# 1. create a bucket
aws s3api create-bucket       --bucket testbucket-1610483598 --region us-east-1

# 2. enable static website hosting
aws s3api put-bucket-website  --bucket testbucket-1610483598 --website-configuration file://website.json

# 3. edit S3 block public access settings
aws s3api put-bucket-acl      --bucket testbucket-1610483598 --region us-east-1 --acl public_read

# 4. add bucket policy that makes content publicly available
aws s3api put-bucket-policy   --bucket testbucket-1610483598 --policy file://bucketpolicy.json

# 5. configure index and error documents
aws s3api put-object          --bucket testbucket-1610483598 --body index.html --key index.html
aws s3api put-object          --bucket testbucket-1610483598 --body error.html --key error.html

#
# 6. test your website endpoint
#     curl http://testbucket-1610483598.s3-website-us-east-1.amazonaws.com/
#

```

