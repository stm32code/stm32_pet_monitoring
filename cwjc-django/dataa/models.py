from django.db import models

# Create your models here.

class User(models.Model):
    uname = models.CharField('用户名',max_length = 128,default="")
    upwd = models.CharField('密码',max_length = 128,default="")
    rname = models.CharField('真实姓名',max_length = 128,default="")
    email = models.CharField('邮箱',max_length = 128,default="")
    phone = models.CharField('手机号',max_length = 128,default="")
    face = models.CharField('角色',max_length = 128,default="")
    token = models.CharField('token', max_length=128, default="")


class StData(models.Model):
    tw = models.CharField('体温', max_length=128, default="")
    xl = models.CharField('心率', max_length=128, default="")
    xy = models.CharField('血氧', max_length=128, default="")
    jd = models.CharField('经度', max_length=128, default="")
    wd = models.CharField('纬度', max_length=128, default="")
    fmq = models.CharField('蜂鸣器', max_length=128, default="")


