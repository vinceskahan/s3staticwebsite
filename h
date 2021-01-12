
MY_BUCKET_NAME="vdstest3"
MY_REGION="us-east-1"

#-- you likely will not need to edit below here--

MY_BUCKET_POLICY="bucketpolicy.json"
MY_WEBSITE_CONFIG="website.json"

if [ ! -f ${MY_WEBSITE_CONFIG} ]
then
    cat > website.json <<- EOF
{
    "IndexDocument": {
        "Suffix": "index.html"
    },
    "ErrorDocument": {
        "Key": "error.html"
    }
}
EOF
fi

if [ ! -f index.html ]
then
    cat > index.html <<EOF
<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
    <title>My Website Home Page</title>
</head>
<body>
  <h1>Welcome to my website</h1>
  <p>Now hosted on Amazon S3!</p>
</body>
</html>
EOF
fi

if [ ! -f error.html ]
then
    cat > error.html <<EOF
<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
    <title>My Website Error Page</title>
</head>
<body>
  <h1>This is an error</h1>
  <p>nothing to see here, move along</p>
</body>
</html>
EOF
fi

if [ ! -f ${MY_BUCKET_POLICY} ]
then
    cat > ${MY_BUCKET_POLICY} <<EOF
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicReadGetObject",
            "Effect": "Allow",
            "Principal": "*",
            "Action": [
                "s3:GetObject"
            ],
            "Resource": [
                "arn:aws:s3:::${MY_BUCKET_NAME}/*"
            ]
        }
    ]
}
EOF
fi

#---- do it to it ----

cat <<EOF

# create bucket
# enable static hosting
# permit public access
# add policy to bucket
# configure index+error docs and upload them
# test it

# 1. create a bucket
aws s3api create-bucket       --bucket ${MY_BUCKET_NAME} --region ${MY_REGION}

# 2. enable static website hosting
aws s3api put-bucket-website  --bucket ${MY_BUCKET_NAME} --website-configuration file://${MY_WEBSITE_CONFIG}

# 3. edit S3 block public access settings
aws s3api put-bucket-acl      --bucket ${MY_BUCKET_NAME} --region ${MY_REGION} --acl public-read 

# 4. add bucket policy that makes content publicly available
aws s3api put-bucket-policy   --bucket ${MY_BUCKET_NAME} --policy file://${MY_BUCKET_POLICY} 

# 5. configure index and error documents
aws s3api put-object          --bucket ${MY_BUCKET_NAME} --body index.html --key index.html
aws s3api put-object          --bucket ${MY_BUCKET_NAME} --body error.html --key error.html

#
# 6. test your website endpoint
#     curl http://${MY_BUCKET_NAME}.s3-website-${MY_REGION}.amazonaws.com/
#

# get the website config
# aws s3api get-bucket-website  --bucket ${MY_BUCKET_NAME}

EOF


