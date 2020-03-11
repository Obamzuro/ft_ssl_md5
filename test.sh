for i in {1..5000}
do
	dd if=/dev/urandom bs=$i count=1 of=ipl 2>&-;
	./ft_ssl base64 ipl | grep -oE '[^ ]+$' > my_base64;
	cat ipl | openssl base64 | sed -z 's/\n//g' > linux_base64; echo '' >> linux_base64;
	diff my_base64 linux_base64;
	./ft_ssl base64 -qd my_base64 > my_decoded_base64;
	diff ipl my_decoded_base64;
	cat ipl | openssl base64 > linux_base64;
	./ft_ssl base64 -qd linux_base64 > my_decoded_base64;
	diff ipl my_decoded_base64;
	echo $i;
done;
