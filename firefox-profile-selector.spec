%if %0{?suse_version} > 0
%if %{?suse_version} > 1310
%bcond_with    qt4
%bcond_without qt5
%else
%bcond_without qt4
%bcond_with    qt5
%endif
%else
%bcond_with    qt4
%bcond_without qt5
%endif
#
Name:           firefox-profile-selector
Version:        0
Release:        0
License:        GPL-2.0
Summary:        Pass URL to FireFox profile
Url:            https://github.com/olafhering/firefox-profile-selector
Source0:        %name-%version.tar.xz
Source1:        https://upload.wikimedia.org/wikipedia/commons/7/76/Mozilla_Firefox_logo_2013.svg
Conflicts:      %name-debuginfo < %version-%release
Conflicts:      %name-debugsource < %version-%release
BuildRequires:  gcc-c++
BuildRequires:  ImageMagick
#
%if %{with qt4}
BuildRequires:  pkgconfig(QtGui)
%define my_qmake qmake-qt4
%if 0%{?suse_version}
%define my_qmake qmake
%endif
%endif
#
%if %{with qt5}
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Widgets)
%define my_qmake qmake-qt5
%endif
#
%description

%prep
%autosetup -p1

%build
%{my_qmake}
make EXTRA_CXXFLAGS='%optflags'

%install
make \
	STRIP=true \
	'INSTALL_ROOT=%buildroot' \
	install
d=%buildroot%_datadir/applications
mkdir -vp "$d"
cp -p *.desktop "$d"

svg='%{S:1}'
for size in 16 22 24 32 48 256
do
  mkdir -p %buildroot%_datadir/icons/hicolor/${size}x${size}/apps/
  convert \
    -density 1200 \
    -resize ${size}x${size} \
    -set date:create "2001-01-01T01:01:0100:00" \
    -set date:modify "2001-01-01T01:01:0100:00" \
    "${svg}" \
    %buildroot%_datadir/icons/hicolor/${size}x${size}/apps/%name.png
done
mkdir -p %buildroot%_datadir/pixmaps
ln -v \
  %buildroot%_datadir/icons/hicolor/${size}x${size}/apps/%name.png \
  %buildroot%_datadir/pixmaps/%name.png
mkdir -vp %buildroot%_datadir/xfce4/helpers/
pushd "$_" > /dev/null
tee %name.desktop <<_EOF_
[Desktop Entry]
Version=1.0
Icon=%name
Type=X-XFCE-Helper
Name=Firefox Profile Selector
StartupNotify=false
X-XFCE-Binaries=%name
X-XFCE-Category=WebBrowser
X-XFCE-Commands=%%B;
X-XFCE-CommandsWithParameter=%%B "%%s";
_EOF_
popd > /dev/null

%files
%license LICENSE
%_bindir/*
%_datadir/applications/*
%_datadir/icons/*
%_datadir/pixmaps/*
%_datadir/xfce4

%changelog
