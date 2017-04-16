ZERO 1.0.6
===========

What is ZERO?
--------------

[ZERO](https://github.com/zerodev2/zero) is a [cryptocurrency](https://en.wikipedia.org/wiki/Cryptocurrency) with advanced privacy features. 
It is a fork of Zcash that is a fork of Bitcoin. The ZERO client software downloads and stores the entire history
of ZERO transactions; depending on the speed of your computer and network connection, the synchronization process
could take a day or more once the blockchain has reached a significant size. [ZERO](https://github.com/zerodev2/zero)
supports two kinds of addresses:
* T addresses (T stands for transparent) - all their transactions can be publicly seen
* Z addresses - their input/ouptut transactions cannot be seen by anyone expect the sender/recipient. These addersses offer privacy

Security Warnings
-----------------
See important security warnings in [doc/security-warnings.md](doc/security-warnings.md).
**ZERO is still a work in progress and highly experimental.** Use at your own risk! Also see: [License and Disclaimer](https://github.com/zerodev2/zero/blob/master/COPYING)

Building & Installing ZERO
--------------------------
Currently only Linux is officially supported. Ubuntu Linux is the recommended distribution to use but others are also possible. 
Requires at least 8GB RAM. Sequence of commands is:

* Install packages (needs to be done once only at start)
```
sudo apt-get install \
build-essential pkg-config libc6-dev m4 g++-multilib \
autoconf libtool ncurses-dev unzip git python \
zlib1g-dev wget bsdmainutils automake
```

* Obtain the ZERO software from GitHub
```
git clone https://github.com/zerodev2/zero.git
cd zero
git checkout master
```

* Download cryptographic keys (needs to be done once only)
```
./zcutil/fetch-params.sh
```

* Build the source code to produce binary executables:
```
./zcutil/build.sh -j$(nproc)
```

* Create a ZERO configuration file
```
mkdir -p ~/.zero
echo "rpcuser=username" > ~/.zero/zero.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.zero/zero.conf
echo "addnode=35.164.216.74" >> ~/.zero/zero.conf
echo "addnode=35.165.120.254" >> ~/.zero/zero.conf
echo "addnode=94.176.235.178" >> ~/.zero/zero.conf
echo "rpcport=23800" >> ~/.zero/zero.conf
echo 'gen=1' >> ~/.zero/zero.conf
echo "genproclimit=$(nproc)" >> ~/.zero/zero.conf
echo 'equihashsolver=tromp' >> ~/.zero/zero.conf
```

After following the build & install steps you will have ZERO ready for use (probably) in folder `~/.zero/src`. The two important binary executables are `zcashd` and `zcash-cli`.

The default configuration in `~/.zero/zero.conf` has mining enabled. When mining you're helping to strengthen the network and contributing to a social good :) 
Mining ZERO may take up to 3 GB per CPU available. If the available memory is not sufficient for this, you may disable mining by setting the option `gen=0`
or you may reduce the number of CPUs that are mining e.g. `genproclimit=1` means mining with 1 CPU only.

Running & Using ZERO
--------------------
The usage is currently the same as for ZCash. For more information see the [ZCash User Guide](https://github.com/zcash/zcash/wiki/1.0-User-Guide#running-zcash).

ZERO Graphical Wallet
---------------------
A [ZERO Graphical Wallet](https://github.com/vaklinov/zero-swing-wallet-ui) exists that is maintained by an independent developer. 
See installtion instruction on the [wallet site](https://github.com/vaklinov/zero-swing-wallet-ui/blob/master/README.md).

![Screenshot](https://github.com/vaklinov/zero-swing-wallet-ui/raw/master/docs/ZeroWallet.png "Main Window")

