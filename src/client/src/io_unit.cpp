#include "../include/io_unit.h"

using namespace iounit;

/**
 * @brief Construct a new IOModel::IOModel object
 * 
 */
IOModel::IOModel()
{
    this->m_handler = std::make_unique <Client::Handler>();
    m_handler.get()->commap_init();
}

/**
 * @brief Destroy the IOModel::IOModel object
 * 
 */
IOModel::~IOModel()
{
    
}