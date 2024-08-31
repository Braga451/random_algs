class Solution {
  public ListNode mergeKLists(ListNode[] unfilteredLists) {
    ListNode[] lists = (unfilteredLists.length > 0 && unfilteredLists[0] != null) ? unfilteredLists
        : Arrays.stream(unfilteredLists).filter(e -> e != null).toArray(ListNode[]::new);

    if (lists.length == 0)
      return null;

    ListNode firstListNode = lists[0];

    for (int i = 1; i < lists.length; i++) {
      ListNode firstListIterator = firstListNode;
      ListNode currentListElementIterator = lists[i];
      ListNode firstListIteratorPrev = firstListIterator;

      while (currentListElementIterator != null) {
        if (firstListIterator == null) {
          firstListIteratorPrev.next = currentListElementIterator;
          break;
        }

        if (firstListIterator.val >= currentListElementIterator.val) {
          if (firstListIterator == firstListNode) {
            firstListNode = currentListElementIterator;
          }

          ListNode nextCurrentListElement = currentListElementIterator.next;

          currentListElementIterator.next = firstListIterator;

          if (firstListIteratorPrev != firstListIterator)
            firstListIteratorPrev.next = currentListElementIterator;

          firstListIteratorPrev = currentListElementIterator;
          currentListElementIterator = nextCurrentListElement;
        } else {
          firstListIteratorPrev = firstListIterator;
          firstListIterator = firstListIterator.next;
        }
      }
    }

    return firstListNode;
  }
}
