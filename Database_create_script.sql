USE [master]
GO
/****** Object:  Database [gloomi]    Script Date: 16/04/2021 09:16:45 ******/
CREATE DATABASE [gloomi]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'gloomi', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\gloomi.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'gloomi_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\gloomi_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [gloomi] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [gloomi].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [gloomi] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [gloomi] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [gloomi] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [gloomi] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [gloomi] SET ARITHABORT OFF 
GO
ALTER DATABASE [gloomi] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [gloomi] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [gloomi] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [gloomi] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [gloomi] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [gloomi] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [gloomi] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [gloomi] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [gloomi] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [gloomi] SET  DISABLE_BROKER 
GO
ALTER DATABASE [gloomi] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [gloomi] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [gloomi] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [gloomi] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [gloomi] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [gloomi] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [gloomi] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [gloomi] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [gloomi] SET  MULTI_USER 
GO
ALTER DATABASE [gloomi] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [gloomi] SET DB_CHAINING OFF 
GO
ALTER DATABASE [gloomi] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [gloomi] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
ALTER DATABASE [gloomi] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [gloomi] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
EXEC sys.sp_db_vardecimal_storage_format N'gloomi', N'ON'
GO
ALTER DATABASE [gloomi] SET QUERY_STORE = OFF
GO
USE [gloomi]
GO
/****** Object:  Table [dbo].[lampen]    Script Date: 16/04/2021 09:16:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[lampen](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[provincie] [nvarchar](max) NOT NULL,
	[stad] [nvarchar](max) NOT NULL,
	[postcode] [nvarchar](max) NOT NULL,
	[apparaatid] [nvarchar](max) NOT NULL,
	[lichtintensiteit] [float] NOT NULL,
	[kleur] [int] NOT NULL,
	[temperatuur] [int] NULL,
	[vochtigheidsgraad] [int] NULL,
	[luxgraad] [int] NULL,
 CONSTRAINT [PK_lampen] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
USE [master]
GO
ALTER DATABASE [gloomi] SET  READ_WRITE 
GO
