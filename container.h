#pragma once

#include <bits/allocator.h>
#include <memory>
#include <cassert>

namespace otus {

    template<class T, class Allocator = std::allocator<T>>
    class List {
    private:
        struct Node {
            explicit Node(T value) : value(std::move(value)) {
            }

            T value;
            Node* next = nullptr;
        };

        struct ListBase {
            Node* node = nullptr;
        };

        using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    public:
        class Iterator {
        public:
            explicit Iterator(Node* node) : node_{node} {
            }

            bool operator==(const Iterator& other) {
                return node_ == other.node_;
            }

            bool operator!=(const Iterator& other) {
                return !(*this == other);
            }

            T operator*() {
                assert(node_ != nullptr);
                return node_->value;
            }

            Iterator& operator++() {
                assert(node_ != nullptr);
                node_ = node_->next;
                return *this;
            }

        private:
            Node* node_;
        };

        explicit List(Allocator allocator = Allocator()) : allocator_{allocator} {
        }

        [[nodiscard]] bool Empty() const {
            AssertConsistency();
            return head_.node == nullptr;
        }

        void PushBack(T value) {
            AssertConsistency();
            Node* new_node = MakeNewNode(std::move(value));
            if (tail_.node == nullptr) {
                head_.node = tail_.node = new_node;
            } else {
                tail_.node->next = new_node;
                tail_.node = tail_.node->next;
            }
        }

        Iterator begin() const {
            return Iterator{head_.node};
        }

        Iterator end() const {
            return Iterator{nullptr};
        }

    private:
        Node* MakeNewNode(T value) {
            Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator_, 1);
            std::allocator_traits<NodeAllocator>::construct(allocator_, new_node, std::move(value));
            return new_node;
        }

        void AssertConsistency() const {
            assert((head_.node == nullptr) == (tail_.node == nullptr));
        }

        ListBase head_;
        ListBase tail_;
        NodeAllocator allocator_;
    };

}  // namespace otus
