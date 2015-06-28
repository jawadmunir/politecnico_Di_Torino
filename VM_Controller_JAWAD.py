import boto
from boto.s3.key import Key
import time
import boto.ec2.connection
from boto.s3.connection import OrdinaryCallingFormat
from boto.s3.connection import S3Connection
from boto.ec2.connection import EC2Connection
from boto.ec2.regioninfo import RegionInfo
from subprocess import call

access_id="Rzh6HjUNRfhuIeBcxqbc5"
access_secret="hRINe4bEGgMQpiuAXZ9T5QtzwWlODAnA8k5QWSYQOF"
host="svc.uc.futuregrid.org"
port=8444
cumulusport=8888
canonical_id="common"

region = RegionInfo(name="nimbus", endpoint=host)
ec2conn = boto.connect_ec2(access_id, access_secret, region=region, port=port)
cf = OrdinaryCallingFormat()
s3conn = S3Connection(access_id, access_secret, host=host, port=cumulusport, is_secure=False, calling_format=cf)



while 1:
    print "**********************************************************************************"
    print "* This is a VM_CONTROLLER.                                                      **\n"
    print "* Enter (list), to get List of avaliable images on futuregrid nimbus platform   **\n"
    print "* Enter (start) to start an EC2 instance                                        **\n"
    print "* Enter (stop) for terminate instances                                          **\n"
    print "* Enter (live) to know about all live instances and there states                **\n"
    print "* Enter (img_atr) to know the attributes of image avaliable                     **\n" 
    print "* Enter (live_atr)to know attribute of live_instance                            **\n"
    print "* Enter (s3) to use simple storage service, to store files.                     **\n"
    print "* Enter (quit) key to exit                                                      **\n"
    print "**********************************************************************************\n\n"
    service=raw_input("Enter service:")
    if service=="list":
        print "******WELCOME TO LIST OF AVALIABLE IMAGES******\n"
        print "The list of all avaliable images are as follows and there image-location are Also given\n"
        images=ec2conn.get_all_images()
        print images
        image = images[0]
        for image in images:
            print 'The image location: %s'% image.location
            
    
            
    elif service=="start":
        while 1:
            print "******WELCOME TO START AN EC2 INSTANCE******\n"
            print "you are starting an EC2 instance\n"
            print "\nEnter (predef) to Launch from already-existing Images \n"
            print "Enter (ownvm) for own Configured my_image\n"
            print "Enter (quit) to quit\n"
            print "******NOTE******\n"
            print "BY ENTERING EVERYTIME IN (predef) AGIAN. WE START A NEW INSTANCE\n"
            print "SO TO START MULTIPLE EC2 INSTANCES, ENVOKE THIS OPTION MULTIPLE TIMES\n"
            print "****************\n" 
            img_op=raw_input("Enter (predef) or (ownvm) or (quit):")
            if img_op=="predef":
                images=ec2conn.get_all_images()
                print images
                img_id=raw_input("\n\n\nEnter image name, choose from above list:")
                reservation = ec2conn.run_instances(image_id=img_id,security_groups=['default'])
                instance = reservation.instances[0]
                # status updates
                while instance.state != 'running':
                    print 'instance is %s' % instance.state
                    time.sleep(30)
                    instance.update()
                print 'instance is %s' % instance.state
                print 'instance dns name:%s' % instance.dns_name
                """Now here you get All the running instances dns_name.
                   Now you can control the remote root by just simple
                   terminal command ( $ ssh root@dns_name ).
                   Or you can ping at ($ PING root@dns_name),
                   one can test if server is active or not"""
                while 1:
                    print "To ssh into root of created i.e remote instance Enter (remote)\n"
                    print "Enter (quit) to quit\n"
                    sname=raw_input("Enter (remote) or (quit):")
                    if sname=="remote":

                    # ssh into root, of the remote instance
                    #print root
                        root="root@"+instance.dns_name
                        call(["ssh", root])
                    elif sname=="quit":
                        print "You decided to quit ssh remote session development"
                        break #out of while
                    else:
                        print "error in keyword\n"
                        
            # Now upload image from own configured VM, And upload it, using S3.
            elif img_op=="ownvm":
                # upload the file according to the Nimbus naming convention
                bucket = s3conn.get_bucket("Repo")
                k = boto.s3.key.Key(bucket)
                k.key = "VMS/%s/%s" % (canonical_id, "my_image")# I have my_image configured by me. 
                k.set_contents_from_filename('/home/jawad/nimbus-cloud-client-021/./my_image')
                # now run the VM
                reservation = ec2conn.run_instances("my_image",security_groups=['default'])
                instance = reservation.instances[0]

                # status updates
                while instance.state != 'running':
                    print 'instance is %s' % instance.state
                    time.sleep(30)
                    instance.update()
                print 'instance is %s' % instance.state
                print 'instance dns name:%s' % instance.dns_name
                """Now here you get All the running instances dns_name.
                   Now you can control the remote root by just simple
                   terminal command ( $ ssh root@dns_name ).
                   Or you can ping at ($ PING root@dns_name),
                   one can test if server is active or not"""
                #print "To ssh into root of created/remote instance enter remote\n"
                while 1:
                    
                    print "To ssh into root of created i.e remote instance Enter (remote)\n"
                    print "Enter (quit) to quit\n"
                    
                    sname=raw_input("Enter (remote) or (quit):")
                    if sname=="remote":
                        # ssh into root, of the remote instance
                        #print root
                            root="root@"+instance.dns_name
                            call(["ssh", root])
                    elif sname=="quit":
                        print "You decided to quit ssh remote session development"
                        break #out of while
                    else:
                        print "error in keyword\n"
            elif img_op=="quit":
                print "you have quit the imp_op,REMEMBER TO TERMINATE ALL YOUR INSTANCES\n"
                print "******GOTO STOP TO TERMINATE ALL YOUR-INSTANCES******\n"
                break
            else:
                print "error in keyword in imp_op\n"
        
                
    # Now Below is to stop all the running instances
    elif service=="stop":
        print "******WELCOME TO STOP ALL LIVE-INSTANCES******\n"
    
        print "All live instances\n"
        
        all_inst = ec2conn.get_all_instances()
        print all_inst
        # iterate through all the matching instances and stop them
        for res in all_inst:

            for instance in res.instances:
                print "Killing %s" % (instance.id)
                instance.terminate()
    elif service=="live":
        print "******WELCOME TO LIST OF ALL YOUR LIVE-INSTANCES******"

        # get a list of all your running instances
        all_inst = ec2conn.get_all_instances()
        print all_inst
        
        # iterate through all of the reservations
        print "Showing all of your current instances"
        for res in all_inst:
            # each reservation have a instance:
            for instance in res.instances:
                print "\t%s : %s : %s" % (instance.id, instance.state, instance.public_dns_name)
                """Now here you get All the running instances dns_name.
                   Now you can control the remote root by just simple
                   terminal command ( $ ssh root@dns_name ).
                   Or you can ping at ($ PING root@dns_name),
                   one can test if server is active or not"""
    elif service=="img_atr":
        print "The list of all avaliable images are as follows and there img_id are Also given\n"
        images=ec2conn.get_all_images()
        print images
        #for i in images:
         #   print '\nimages_name: %s and its img_id: %s'% (i, images.id)
        
        print "Enter the image you want attributes of\n"
        img_at=raw_input("Enter img_id:")
        att = ec2conn.get_image_attribute(img_at)
        print att
    elif service=="live_atr":
        all_inst = ec2conn.get_all_instances()
        print all_inst
        print "Enter the image_id you want to see attributes and attribute you want\n"
        live_at=raw_input("Enter live instance_id:")
        attribute=raw_input("Enter attribute:")
        latt = ec2conn.get_instance_attribute(live_at,attribute)
        print latt
    elif service=="s3":
        print "Already existing buckets are\n"
        rs= s3conn.get_all_buckets()
        c=len(rs)
        print 'The no of already existing buckets %s' % c
        for b in rs:
            print "The buckets names are\n"
            print  b.name
            #bucket.delete()
        print "Enter name for bucket\n"
        bucket_name=raw_input("Enter bucket_name:")
        bucket=s3conn.create_bucket(bucket_name)
        k=Key(bucket)
        k.key = 'myfile'
        print "Enter filenames \n"
        cn=raw_input("Enter source_file_name:")
        df=raw_input("Enter des_file_name:")
        k.set_content_from_filename(cn)
        k.get_content_from_filename(df)
    elif service=="quit":
        print "You have quited the VM_CONTROLLER"
        
        break
    else:
        print "Enter the correct service you need\n"
        
        
        
     
