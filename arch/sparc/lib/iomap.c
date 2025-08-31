/*
 * Implement the sparc iomap interfaces
 */
#include <linux/pci.h>
#include <linux/module.h>
#include <asm/io.h>

/* Create a virtual mapping cookie for an IO port range */
void __iomem *ioport_map(unsigned long port, unsigned int nr)
{
	return (void __iomem *) (unsigned long) port;
}

void ioport_unmap(void __iomem *addr)
{
	/* Nothing to do */
}
/* DISABLED: EXPORT_SYMBOL(ioport_map); */
/* DISABLED: EXPORT_SYMBOL(ioport_unmap); */

void pci_iounmap(struct pci_dev *dev, void __iomem * addr)
{
	/* nothing to do */
}
/* DISABLED: EXPORT_SYMBOL(pci_iounmap); */
