#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ip.h>

struct net_device *proxydev;

int nettap_open(struct net_device *dev)
{
	pr_info("+%s+\n", __func__);
	return 0;
}

netdev_tx_t nettap_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct iphdr *iph;
	pr_info("+%s+\n", __func__);
	
	iph = ip_hdr(skb);
	pr_info("protocol = %d\n", iph->protocol);
	return 0;
}

int nettap_stop(struct net_device *dev)
{
	pr_info("+%s+\n", __func__);
	return 0;
}

static const struct net_device_ops proxydev_ops = {
	.ndo_open		= nettap_open,
	.ndo_start_xmit		= nettap_start_xmit,
	.ndo_stop		= nettap_stop
};

static int nettap_init(void)
{
	int ret;
	struct net_device *dev;
	pr_info("--%s--\n", __func__);

	proxydev = alloc_etherdev(0);
	if (!proxydev) {
		pr_err("alloc_etherdev() failed\n");
		return -1;
	}

	proxydev->netdev_ops = &proxydev_ops;
		
	ret = register_netdev(proxydev);
	if (ret) {
		pr_err("register_netdev() failed\n");
		return -1;
	}
	
	
	rcu_read_lock();
	for_each_netdev_rcu(&init_net, dev) {
		printk("[%s] ", dev->name);
	}
	rcu_read_unlock();
	return 0;
}

static void nettap_exit(void)
{
	printk("--%s--\n", __func__);
	if(proxydev) {
		unregister_netdev(proxydev);
		free_netdev(proxydev);
	}

	return;
}

module_init(nettap_init);
module_exit(nettap_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_INFO(intree, "Y");
